
// import packages from java
import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Random;
import java.util.Scanner;

// Initial pile of socks
public class sockPile {
    // number of different sock colors
    public int numSocksCategory;
    // name of the colors
    public String[] socks_category = {"white","blue","grey","black"};
    // Store the pile of socks
    ArrayList<String> pile;
    // Total number of socks in the pile
    public int numSocks;

    // Constructor for the sockPile class 
    public sockPile(){
        // get number of distinct sock colors
        numSocksCategory = socks_category.length;
        // initialse the arraylist
        pile = new ArrayList<String>();
        // read input from file
        try{
            readInputFromFile();
        }
        catch(FileNotFoundException e){
            // display error if file not found
            System.out.println("No input file found");
            // Exit from the code with code 0 if no input file found
            System.exit(0);
        }
        // display the socks present in the input pile
        DisplaySockPile();
    }

    // Function fills the pile from user input
    public void readInputFromFile() throws FileNotFoundException{
        // get path for the input file
        String path = System.getProperty("user.dir") +"/input.txt";
        // open an instance of new file
        File f = new File(path);
        // scanner to read from the file
        Scanner S = new Scanner(f);
        // Read the color of each sock and add to the file
        while(S.hasNext()){
            pile.add(S.next());
        }
        // number of socks
        numSocks = pile.size();
    }

    public void DisplaySockPile(){
        // dispaly the socks that are present in the array
        System.out.println("The pile of socks contains the following socks :");
        for(int i=0;i<numSocks;i++){
            System.out.print(pile.get(i) + " ");
        }
        System.out.println("\n");
    }
}
