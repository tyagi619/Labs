// Matching machine
public class matchMachine implements Runnable {
    // Stores the count of socks corresponding to each category
    private int[] sockCount;
    // Number of different colors of socks
    private int numSocksCategory;
    // color names of the socks
    private String[] sock_category;
    // shelf machine instance
    private shelfMachine SM;
    // Number of robotic arms that have finished execution
    private Integer end;
    // Number of robotic arms in total
    private int numRoboticArms;

    // Constructor for matching machine
    public matchMachine(int n,String[] category,shelfMachine s,int numArms){
        // Set number of total robotic arms
        numRoboticArms = numArms; 
        // set the instance of shelf machine
        SM = s;
        // set number of socks category
        numSocksCategory = n;
        sockCount = new int[n];
        sock_category = new String[n];
        // Initialise count of each sock color to be 0 since intially all the socks are 
        // in the pile with robotic Arms
        for(int i=0;i<n;i++){
            sockCount[i] = 0;
            sock_category[i] = category[i];
        }
        // Initially no arm has finished execution
        end = 0;
    }

    // Function recieves a sock from one of the robotic arm
    public void passToMatchMachine(String sockColor){
        // Prevent multiple robotic from manipulating the sock count in a single time
        // since it can create race condition and the results may not be satisfactory
        synchronized(sockCount){
            // Check the color of sock recieved from the robotic arm
            for(int i=0;i<numSocksCategory;i++){
                if(sockColor.equals(sock_category[i])){
                    // increase the count of socks for the matching color by 1
                    sockCount[i]++;
                    break;
                }
            }
        }
    }

    // Function is invoked when a robotic arm finishes its execution
    public void signalExecutionEnd(){
        // Multiple arms may finish execution at the same time
        // Thus we need synchrinization when changing the value of end variable
        synchronized((Integer)end){
            end += 1;
        }
    }
    // used to run the process as a separate thread
    @Override
    public void run() {
        boolean pairExists = true;
        // while robotic arms are executing
        while(end!=numRoboticArms| pairExists){
            // If any robotic arm is still running, there may be pairs formed
            if(end!=numRoboticArms) pairExists = true;
            // else look for existing buffer for available pending pair formation
            else pairExists = false;
            // Find socks of same color that may form pair
            for(int i=0;i<numSocksCategory;i++){
                // Robotic arms may try to increase sock count while
                // matching machine will decrease count.Since both may occur simultaneously
                // We need a synchronization over the sockCount 
                synchronized(sockCount){
                    // If a pair of the given color exists or is formed
                    if(sockCount[i]>=2){
                        // Remove the socks pair 
                        sockCount[i]-=2;
                        System.out.println("Matching Machine found a pair of " + sock_category[i] + " socks. Forwarding to Shelf Machine....");
                        // Pass the sock pair to the shelf machine
                        SM.passToShelfMachine(sock_category[i]);
                    }
                    // If still there are pairs of socks available
                    // pick them in next iteration
                    if(sockCount[i]>=2){
                        pairExists = pairExists || true;
                    }
                }
            }
        }
        // Signal to shelf machine that matching machine has finished execution
        SM.signalEnd();
    }
}
