import java.util.Scanner;
// Robotic arm class
public class roboticArm implements Runnable {
    // Pile of socks
    private sockPile sockHeap;
    // Robotic Arm id
    private int robotId;
    // matching machine instance
    private matchMachine M;
    // number of simultaneous robotic arms
    private int numThreads;

    // Constructor for roboticArm class
    public roboticArm(int id,sockPile sp,matchMachine mm,int numRoboticArms){
        robotId = id; //initialise robotic arm id
        sockHeap = sp; //initialise pile of socks
        M = mm; //set instance of matching machine
        numThreads = numRoboticArms; // set number of robotic arm threads
    }

    @Override
    public void run() {
        // ith robot start from i-1 th index from pile and picks 
        // every numThreads sock starting from i-1 index 
        int startIndex = robotId-1;
        // This divides the data equally among the robotic arms
        for(int i=startIndex;i<sockHeap.numSocks;i+=numThreads){
            System.out.println("Robot Arm :" + robotId + " picked up " + sockHeap.pile.get(i) + " from the pile");
            // Pass the sock to matching machine
            M.passToMatchMachine(sockHeap.pile.get(i));
        }
        M.signalExecutionEnd();
        // End execution when there are no more socks to pick
        System.out.println("Robot Arm :" + robotId + " finished execution");
    }

    // main method where execution starts
    public static void main(String[] args) {
        // Set number of robotic arms to 4. Change this number to change number of robotic arms
        int numRoboticArm = 4;
        // Initialise a socks pile object
        sockPile sp = new sockPile();
        // Initialise an instance of shelf machine
        shelfMachine sm = new shelfMachine(sp.numSocksCategory, sp.socks_category);
        // initialise an instance of matching machine
        matchMachine mm = new matchMachine(sp.numSocksCategory, sp.socks_category, sm,numRoboticArm);

        // Initialise instances of robotic arms with a single matching machine and shelf machine
        roboticArm[] arms = new roboticArm[numRoboticArm];
        for(int i=0;i<numRoboticArm;i++){
            arms[i] = new roboticArm(i+1,sp,mm,numRoboticArm);
        }
        // Create a separate thread for shelf machine
        Thread smThread = new Thread(sm);
        smThread.start();
        // Create a separate thread for matching machine
        Thread mmThread = new Thread(mm);
        mmThread.start();

        // Start 4 threads for each robotic arm
        Thread[] threads = new Thread[numRoboticArm];
        for(int i=0;i<numRoboticArm;i++){
            threads[i] = new Thread(arms[i]);
            threads[i].start();
        }
        
        // Wait for the threads to end execution
        for(int i=0;i<numRoboticArm;i++){
            try{
                threads[i].join();
            }catch(InterruptedException e){
            }
        }

        try{
            // Wait for matching machine to end
            mmThread.join();
            // Wait for shelf machine to end
            smThread.join();
        }
        catch(InterruptedException e){}
        
        
        // Display execution completion message
        System.out.println("All robotic arms finished execution");
    } 
}
