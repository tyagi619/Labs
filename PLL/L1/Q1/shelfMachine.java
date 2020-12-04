// Shelf Machine
public class shelfMachine implements Runnable {
    // Count of pair of socks corresponding to each color
    private int[] sockPairCount;
    // various possible color of socks
    private String[] sock_category;
    // number of distinct sock color
    private int numSocksCategory;
    // true means that the matching machine has finished execution
    boolean end;

    // COnstructor for shelf machine
    public shelfMachine(int n,String[] category){
        numSocksCategory = n;
        sockPairCount = new int[n];
        sock_category = new String[n];
        // set count of sock pair for each color to 0
        // since initially the shelf machine has no socks
        for(int i=0;i<n;i++){
            sockPairCount[i] = 0;
            sock_category[i] = category[i];
        }
        // Initially the matching machine will execute
        end=false;
    }

    // Function is invoked when matching machine completes its execution
    public void signalEnd(){
        end = true;
    }

    // Function recieves a pair of socks from matching machine
    public void passToShelfMachine(String sockPairColor){
        // No synchronization is required since only a single matching
        // machine passes socks to shelf machine

        // Find the color of the sock pair recieved
        for(int i=0;i<numSocksCategory;i++){
            synchronized(sockPairCount){
                if(sockPairColor.equals(sock_category[i])){
                    sockPairCount[i] += 1;
                    // Put the sock pair on the corresponding shelf
                    
                    break;
                }
            }
        }
    }

    @Override
    public void run() {
        // boolean varible to tell if there are pairs available to be kept to shelf
        boolean pairExists = true;
        // Continue till the matching machine is executing or until there are pairs
        // to be kept to shelf whichever occurs later in time
        while(!end || pairExists){
            // If matching machine is still executing, there may be pairs available
            if(!end) pairExists = true;
            // else we need to look from the collection of available pending pairs
            else pairExists = false;
            for(int i=0;i<numSocksCategory;i++){
                synchronized(sockPairCount){
                    // Check if there is a pair available for the ith color socks
                    if(sockPairCount[i]>0){
                        // Put sock pair to the shelf
                        sockPairCount[i] -= 1;
                        // DIsplay the output message
                        System.out.println("Shelf Manager recieved a " + sock_category[i] + " pair. "
                        + sock_category[i] + " pair moved to shelf " + Integer.toString(i+1));            
                    }
                    // If there are more pairs of same colour handle them in next iteration
                    pairExists = pairExists || (sockPairCount[i]>0);
                }
            }
        }
    }
}
