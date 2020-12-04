#include <fstream>
#include <string>

#include "ns3/applications-module.h"
#include "ns3/core-module.h"
#include "ns3/flow-monitor-module.h"
#include "ns3/gnuplot.h"
#include "ns3/internet-module.h"
#include "ns3/ipv4-global-routing-helper.h"
#include "ns3/network-module.h"
#include "ns3/point-to-point-layout-module.h"
#include "ns3/point-to-point-module.h"

using namespace ns3;
Gnuplot2dDataset dataset;
Gnuplot2dDataset datasetTcp;
Gnuplot2dDataset datasetUdp;
uint32_t pktSize = 1500;
uint32_t bufferSize = 50 * pktSize;
NS_LOG_COMPONENT_DEFINE("Assignment_4");
/*
Custom application for binding the socket at application initiation time
and to increase the data rate at run time.
This is taken from ns3 examples.
*/
class MyApp : public Application {
   public:
    MyApp();
    virtual ~MyApp();

    void Setup(Ptr<Socket> socket, Address address, uint32_t pktSize,
               uint32_t nPackets, DataRate dataRate);
    void ChangeRate(DataRate newrate);

   private:
    virtual void StartApplication(void);
    virtual void StopApplication(void);

    void ScheduleTx(void);
    void SendPacket(void);

    Ptr<Socket> m_socket;
    Address m_peer;
    uint32_t m_pktSize;
    uint32_t m_nPackets;
    DataRate m_dataRate;
    EventId m_sendEvent;
    bool m_running;
    uint32_t m_packetsSent;
};

MyApp::MyApp()
    : m_socket(0),
      m_peer(),
      m_pktSize(0),
      m_nPackets(0),
      m_dataRate(0),
      m_sendEvent(),
      m_running(false),
      m_packetsSent(0) {}

MyApp::~MyApp() { m_socket = 0; }

void MyApp::Setup(Ptr<Socket> socket, Address address, uint32_t pktSize,
                  uint32_t nPackets, DataRate dataRate) {
    m_socket = socket;
    m_peer = address;
    m_pktSize = pktSize;
    m_nPackets = nPackets;
    m_dataRate = dataRate;
}

void MyApp::StartApplication(void) {
    m_running = true;
    m_packetsSent = 0;
    m_socket->Bind();
    m_socket->Connect(m_peer);
    SendPacket();
}

void MyApp::StopApplication(void) {
    m_running = false;

    if (m_sendEvent.IsRunning()) {
        Simulator::Cancel(m_sendEvent);
    }

    if (m_socket) {
        m_socket->Close();
    }
}

void MyApp::SendPacket(void) {
    Ptr<Packet> packet = Create<Packet>(m_pktSize);
    m_socket->Send(packet);

    if (++m_packetsSent < m_nPackets) {
        ScheduleTx();
    }
}

void MyApp::ScheduleTx(void) {
    if (m_running) {
        Time tNext(Seconds(m_pktSize * 8 /
                           static_cast<double>(m_dataRate.GetBitRate())));
        m_sendEvent = Simulator::Schedule(tNext, &MyApp::SendPacket, this);
    }
}

void MyApp::ChangeRate(DataRate newrate) {
    m_dataRate = newrate;
    return;
}

// This function is used to change the data rate of an application
void IncRate(Ptr<MyApp> app, DataRate rate) {
    app->ChangeRate(rate);
    return;
}

// Throughput calculating function, to calculate throughput at every second
void Throughput(FlowMonitorHelper *fmhelper, Ptr<FlowMonitor> flowMon) {
    Ptr<Ipv4FlowClassifier> classifier =
        DynamicCast<Ipv4FlowClassifier>(fmhelper->GetClassifier());
    std::map<FlowId, FlowMonitor::FlowStats> stats = flowMon->GetFlowStats();
    double sumFlow = 0, sumFlowSqr = 0, sumFlowTCP = 0;
    for (std::map<FlowId, FlowMonitor::FlowStats>::const_iterator i =
             stats.begin();
         i != stats.end(); ++i) {
        Ipv4FlowClassifier::FiveTuple t = classifier->FindFlow(i->first);
        // Calculating the throughput
        double TPut = i->second.rxBytes * 8.0 /
                      (i->second.timeLastRxPacket.GetSeconds() -
                       i->second.timeFirstTxPacket.GetSeconds()) /
                      1000000;
        sumFlow += TPut;
        sumFlowSqr += TPut * TPut;
        sumFlowTCP += TPut;
        if (t.destinationPort == 3003 || t.destinationPort == 3004 || t.destinationPort == 3005)
            sumFlowTCP -= TPut;
    }
    // Calculating the fairness
    double FairnessIndex = (sumFlow * sumFlow) / (6 * sumFlowSqr);
    dataset.Add((double)Simulator::Now().GetSeconds(), FairnessIndex);
    if (sumFlowTCP != 0)
        datasetTcp.Add((double)Simulator::Now().GetSeconds(), sumFlowTCP);
    if (sumFlow - sumFlowTCP != 0)
        datasetUdp.Add((double)Simulator::Now().GetSeconds(),
                       sumFlow - sumFlowTCP);
    std ::cout << " FairnessIndex: " << FairnessIndex << std ::endl;
    Simulator::Schedule(Seconds(1), &Throughput, fmhelper, flowMon);
}

int main(int argc, char *argv[]) {
    // The smallest measurable time interval is 1 ns
    Time::SetResolution(Time::NS);

    // Set default configration as TCP New Reno
    Config::SetDefault("ns3::TcpL4Protocol::SocketType", TypeIdValue(TcpNewReno::GetTypeId()));

    // Start and end time of applications
    uint32_t st_time = 0;
    uint32_t start_time_apps = 1;
    // run time of applications
    uint32_t end_time = 20;

    uint32_t packetsToSend = 1000000;

    // Instantiate the dataset, set its title, and make the points be
    // plotted along with connecting lines.
    // Gnuplot2dDataset dataset;
    // Gnuplot2dDataset datasetTcp;
    // Gnuplot2dDataset datasetUdp;
    dataset.SetTitle("Fairness");
    dataset.SetStyle(Gnuplot2dDataset::LINES_POINTS);
    datasetTcp.SetTitle("TCP flow");
    datasetTcp.SetStyle(Gnuplot2dDataset::LINES_POINTS);
    datasetUdp.SetTitle("UDP flow");
    datasetUdp.SetStyle(Gnuplot2dDataset::LINES_POINTS);

    // Initialization Complete

    CommandLine cmd;
    cmd.Parse(argc, argv);

    /* Network topology

        h1  n0                                   n5     h4
               \ 100 Mbps, 10ms                /
                \          10Mbps, 100ms      /
        h2  n1---n3-------------------------n4 ----n6   h5
                /                             \
               / 100 Mbps, 10ms                \
        h3  n2                                  n7      h6


    Connections 
    
    h1-h4/n0-n5 TCP
    h2-h5/n1-n6 TCP
    h2-h3/n1-n2 TCP
    h3-h6/n2-n7 UDP
    h1-h5/n0-n6 UDP
    h4-h6/n5-n7 UDP
*/

    // Creating a node container to hold the 8 nodes
    NodeContainer nodes;
    nodes.Create(8);

    // Create node containers for every link
    NodeContainer n0n3 = NodeContainer(nodes.Get(0), nodes.Get(3));  // h1r1
    NodeContainer n1n3 = NodeContainer(nodes.Get(1), nodes.Get(3));  // h2r1
    NodeContainer n2n3 = NodeContainer(nodes.Get(2), nodes.Get(3));  // h3r1
    NodeContainer n3n4 = NodeContainer(nodes.Get(3), nodes.Get(4));  // r1r2
    NodeContainer n4n5 = NodeContainer(nodes.Get(4), nodes.Get(5));  // r2h4
    NodeContainer n4n6 = NodeContainer(nodes.Get(4), nodes.Get(6));  // r2h5
    NodeContainer n4n7 = NodeContainer(nodes.Get(4), nodes.Get(7));  // r2h6

    // Install the internet stack(protocols) on the nodes
    InternetStackHelper internet;
    internet.Install(nodes);

    // Create point to point channels between the nodes
    PointToPointHelper p2p;
    // Host to router links
    p2p.SetDeviceAttribute("DataRate", StringValue("100Mbps"));
    p2p.SetChannelAttribute("Delay", StringValue("10ms"));
    NetDeviceContainer d0d3 = p2p.Install(n0n3);
    NetDeviceContainer d1d3 = p2p.Install(n1n3);
    NetDeviceContainer d2d3 = p2p.Install(n2n3);
    NetDeviceContainer d4d5 = p2p.Install(n4n5);
    NetDeviceContainer d4d6 = p2p.Install(n4n6);
    NetDeviceContainer d4d7 = p2p.Install(n4n7);
    // Router to router links
    p2p.SetQueue("ns3::DropTailQueue", "MaxSize", StringValue(std::to_string(100000 * 10 / pktSize) + 'p'));
    p2p.SetDeviceAttribute("DataRate", StringValue("10Mbps"));
    p2p.SetChannelAttribute("Delay", StringValue("100ms"));
    NetDeviceContainer d3d4 = p2p.Install(n3n4);

    // Assign IP addresses to every interface
    Ipv4AddressHelper ipv4;
    ipv4.SetBase("10.1.1.0", "255.255.255.0");
    Ipv4InterfaceContainer i0i3 = ipv4.Assign(d0d3);

    ipv4.SetBase("10.1.2.0", "255.255.255.0");
    Ipv4InterfaceContainer i1i3 = ipv4.Assign(d1d3);

    ipv4.SetBase("10.1.3.0", "255.255.255.0");
    Ipv4InterfaceContainer i2i3 = ipv4.Assign(d2d3);

    ipv4.SetBase("10.1.4.0", "255.255.255.0");
    Ipv4InterfaceContainer i3i4 = ipv4.Assign(d3d4);

    ipv4.SetBase("10.1.5.0", "255.255.255.0");
    Ipv4InterfaceContainer i4i5 = ipv4.Assign(d4d5);

    ipv4.SetBase("10.1.6.0", "255.255.255.0");
    Ipv4InterfaceContainer i4i6 = ipv4.Assign(d4d6);

    ipv4.SetBase("10.1.7.0", "255.255.255.0");
    Ipv4InterfaceContainer i4i7 = ipv4.Assign(d4d7);

    Ipv4GlobalRoutingHelper::PopulateRoutingTables();

    /*
       TCP flows
   */

    //  h1-h4/n0-n5 TCP ,Server n0
    uint16_t snkport1 = 3000;

    // Creating sink
    Address sinkAdd1(InetSocketAddress(i4i5.GetAddress(1), snkport1));
    PacketSinkHelper packetSink1("ns3::TcpSocketFactory", InetSocketAddress(Ipv4Address::GetAny(), snkport1));

    // Sink application using packet sink helper which consumes all packets from port1
    ApplicationContainer sinkApps1 = packetSink1.Install(nodes.Get(5));
    sinkApps1.Start(Seconds(st_time));
    sinkApps1.Stop(Seconds(end_time));

    // Creating a tcp socket for sender application
    Ptr<Socket> tcpSocket1 = Socket::CreateSocket(nodes.Get(0), TcpSocketFactory::GetTypeId());
    tcpSocket1->SetAttribute("SndBufSize", ns3::UintegerValue(bufferSize));
    tcpSocket1->SetAttribute("RcvBufSize", ns3::UintegerValue(bufferSize));

    // Creating sender application
    Ptr<MyApp> tcp_Agent1 = CreateObject<MyApp>();
    tcp_Agent1->Setup(tcpSocket1, sinkAdd1, pktSize, packetsToSend, DataRate("20Mbps"));
    nodes.Get(0)->AddApplication(tcp_Agent1);
    tcp_Agent1->SetStartTime(Seconds(start_time_apps));
    tcp_Agent1->SetStopTime(Seconds(end_time));

    // h2-h5/n1-n6 TCP ,Server n6
    uint16_t port2 = 3001;

    // Creating sink
    Address sinkAdd2(InetSocketAddress(i1i3.GetAddress(0), port2));
    PacketSinkHelper packetSink2("ns3::TcpSocketFactory", InetSocketAddress(Ipv4Address::GetAny(), port2));

    // Creating a sink application to consume all packets from the above port
    ApplicationContainer sinkApps2 = packetSink2.Install(nodes.Get(1));
    sinkApps2.Start(Seconds(st_time));
    sinkApps2.Stop(Seconds(end_time));

    // Creating socket
    Ptr<Socket> tcpSocket2 = Socket::CreateSocket(nodes.Get(6), TcpSocketFactory::GetTypeId());
    tcpSocket2->SetAttribute("SndBufSize", ns3::UintegerValue(bufferSize));
    tcpSocket2->SetAttribute("RcvBufSize", ns3::UintegerValue(bufferSize));

    // Creating sender application
    Ptr<MyApp> tcp_Agent2 = CreateObject<MyApp>();
    tcp_Agent2->Setup(tcpSocket2, sinkAdd2, pktSize, packetsToSend, DataRate("20Mbps"));
    nodes.Get(6)->AddApplication(tcp_Agent2);
    tcp_Agent2->SetStartTime(Seconds(start_time_apps));
    tcp_Agent2->SetStopTime(Seconds(end_time));

    // h2-h3/n1-n2 TCP ,Server n2
    uint16_t port3 = 3002;
    // Creating sink
    Address sinkAdd3(InetSocketAddress(i1i3.GetAddress(0), port3));
    PacketSinkHelper packetSink3("ns3::TcpSocketFactory", InetSocketAddress(Ipv4Address::GetAny(), port3));

    // Creating a sink application to consume all packets from the above port
    ApplicationContainer sinkApps3 = packetSink3.Install(nodes.Get(1));
    sinkApps3.Start(Seconds(st_time));
    sinkApps3.Stop(Seconds(end_time));

    // Creating socket
    Ptr<Socket> tcpSocket3 = Socket::CreateSocket(nodes.Get(2), TcpSocketFactory::GetTypeId());
    tcpSocket3->SetAttribute("SndBufSize", ns3::UintegerValue(bufferSize));
    tcpSocket3->SetAttribute("RcvBufSize", ns3::UintegerValue(bufferSize));

    // Creating sender application
    Ptr<MyApp> tcp_Agent3 = CreateObject<MyApp>();
    tcp_Agent3->Setup(tcpSocket3, sinkAdd3, pktSize, packetsToSend, DataRate("20Mbps"));
    nodes.Get(2)->AddApplication(tcp_Agent3);
    tcp_Agent3->SetStartTime(Seconds(start_time_apps));
    tcp_Agent3->SetStopTime(Seconds(end_time));

    /*
     *CBR traffic on UDP
     */

    // h4-h6/n5-n7 UDP
    uint16_t port4 = 3003;
    // Creating sink
    Address sinkAdd4(InetSocketAddress(i4i7.GetAddress(1), port4));
    PacketSinkHelper packetSink4("ns3::UdpSocketFactory", InetSocketAddress(Ipv4Address::GetAny(), port4));

    // Creating a sink application to consume all packets from the above port
    ApplicationContainer sinkApps4 = packetSink4.Install(nodes.Get(7));
    sinkApps4.Start(Seconds(st_time));
    sinkApps4.Stop(Seconds(end_time));

    // Creating socket
    Ptr<Socket> ns3UdpSocket4 = Socket::CreateSocket(nodes.Get(5), UdpSocketFactory::GetTypeId());
    ns3UdpSocket4->SetAttribute("RcvBufSize", ns3::UintegerValue(bufferSize));

    // Creating sender application
    Ptr<MyApp> udp_Agent0 = CreateObject<MyApp>();
    udp_Agent0->Setup(ns3UdpSocket4, sinkAdd4, pktSize, packetsToSend, DataRate("20Mbps"));
    nodes.Get(5)->AddApplication(udp_Agent0);
    udp_Agent0->SetStartTime(Seconds(start_time_apps));
    udp_Agent0->SetStopTime(Seconds(end_time));

    // h3-h6/n2-n7 UDP
    uint16_t port5 = 3004;
    // Creating sink
    Address sinkAdd5(InetSocketAddress(i2i3.GetAddress(0), port5));
    PacketSinkHelper packetSink5("ns3::UdpSocketFactory", InetSocketAddress(Ipv4Address::GetAny(), port5));
    // Creating a sink application to consume all packets from the above port
    ApplicationContainer sinkApps5 = packetSink5.Install(nodes.Get(2));
    sinkApps5.Start(Seconds(st_time));
    sinkApps5.Stop(Seconds(end_time));

    // Creating socket
    Ptr<Socket> ns3UdpSocket5 = Socket::CreateSocket(nodes.Get(7), UdpSocketFactory::GetTypeId());
    ns3UdpSocket5->SetAttribute("RcvBufSize", ns3::UintegerValue(bufferSize));

    // Creating sender application
    Ptr<MyApp> udp_Agent1 = CreateObject<MyApp>();
    udp_Agent1->Setup(ns3UdpSocket5, sinkAdd5, pktSize, packetsToSend, DataRate("20Mbps"));
    nodes.Get(7)->AddApplication(udp_Agent1);
    udp_Agent1->SetStartTime(Seconds(start_time_apps));
    udp_Agent1->SetStopTime(Seconds(end_time));

    Simulator::Schedule(Seconds(10.0), &IncRate, udp_Agent1, DataRate("100Mbps"));

    // h1-h5/n0-n6 UDP
    uint16_t port6 = 3005;
    // Creating sink
    Address sinkAdd6(InetSocketAddress(i4i6.GetAddress(1), port6));
    PacketSinkHelper packetSink6("ns3::UdpSocketFactory", InetSocketAddress(Ipv4Address::GetAny(), port6));

    // Creating a sink application to consume all packets from the above port
    ApplicationContainer sinkApps6 = packetSink6.Install(nodes.Get(6));
    sinkApps6.Start(Seconds(st_time));
    sinkApps6.Stop(Seconds(end_time));

    // Creating socket
    Ptr<Socket> ns3UdpSocket6 = Socket::CreateSocket(nodes.Get(0), UdpSocketFactory::GetTypeId());
    ns3UdpSocket6->SetAttribute("RcvBufSize", ns3::UintegerValue(bufferSize));

    // Creating sender application
    Ptr<MyApp> udp_Agent2 = CreateObject<MyApp>();
    udp_Agent2->Setup(ns3UdpSocket6, sinkAdd6, pktSize, packetsToSend, DataRate("20Mbps"));
    nodes.Get(0)->AddApplication(udp_Agent2);
    udp_Agent2->SetStartTime(Seconds(start_time_apps));
    udp_Agent2->SetStopTime(Seconds(end_time));

    /*
      *********************************
        Analyze flow using flowmonitor
      *********************************
    */

    Ptr<FlowMonitor> flowMonitor;
    FlowMonitorHelper flowHelper;
    flowMonitor = flowHelper.InstallAll();

    // Passing the flowmonitor and helper through the Throughput function
    Throughput(&flowHelper, flowMonitor);

    NS_LOG_INFO("Run Simulation.");
    Simulator::Stop(Seconds(20.0));
    Simulator::Run();
    Simulator::Destroy();

    // Initialize Plot

    std ::string fileNameWithNoExtension = "UDPIncreaseFairness";
    std ::string graphicsFileName = fileNameWithNoExtension + ".png";
    std ::string plotFileName = fileNameWithNoExtension + ".plt";
    std ::string plotTitle = "Time v/s Fairness";

    std ::string fileNameWithNoExtensionTcp = "UDPIncreaseTCP";
    std ::string graphicsFileNameTcp = fileNameWithNoExtensionTcp + ".png";
    std ::string plotFileNameTcp = fileNameWithNoExtensionTcp + ".plt";
    std ::string plotTitleTcp = "Time v/s Throughput(TCP)";

    std ::string fileNameWithNoExtensionUdp = "UDPIncreaseUDP";
    std ::string graphicsFileNameUdp = fileNameWithNoExtensionUdp + ".png";
    std ::string plotFileNameUdp = fileNameWithNoExtensionUdp + ".plt";
    std ::string plotTitleUdp = "Time v/s Throughput(UDP)";

    // Instantiate the plot and set its title.
    Gnuplot plot(graphicsFileName);
    Gnuplot plot_tcp(graphicsFileNameTcp);
    Gnuplot plot_udp(graphicsFileNameUdp);
    plot.SetTitle(plotTitle);
    plot_tcp.SetTitle(plotTitleTcp);
    plot_udp.SetTitle(plotTitleUdp);

    // Make the graphics file, which the plot file will create when it is used with Gnuplot, be a PNG file.
    plot.SetTerminal("png");
    plot_tcp.SetTerminal("png");
    plot_udp.SetTerminal("png");

    // Set the labels for each axis.
    plot.SetLegend("Time (seconds)", "Fairness");
    plot_tcp.SetLegend("Time (seconds)", "Throughput (mbps)");
    plot_udp.SetLegend("Time (seconds)", "Throughput (mbps)");

    plot.AppendExtra("set xrange [0:20]");
    plot_tcp.AppendExtra("set xrange [0:20]");
    plot_udp.AppendExtra("set xrange [0:20]");

    // Add the dataset to the plot.
    plot.AddDataset(dataset);
    plot_udp.AddDataset(datasetUdp);
    plot_tcp.AddDataset(datasetTcp);

    // Open the plot file.
    std::ofstream plotFile(plotFileName.c_str());
    // Write the plot file.
    plot.GenerateOutput(plotFile);
    // Close the plot file.
    plotFile.close();

    std::ofstream plotFile_tcp(plotFileNameTcp.c_str());
    plot_tcp.GenerateOutput(plotFile_tcp);
    plotFile_tcp.close();

    std::ofstream plotFile_udp(plotFileNameUdp.c_str());
    plot_udp.GenerateOutput(plotFile_udp);
    plotFile_udp.close();

    NS_LOG_INFO("Done.");
}