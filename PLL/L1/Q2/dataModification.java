// import packages from java
import java.io.File;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.channels.FileChannel;
import java.nio.channels.FileLock;
import java.nio.file.StandardOpenOption;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.Scanner;
import java.nio.file.Path;
import java.nio.file.Paths;

// Main class
public class dataModification {
    // File column headers
    public String header = "Roll No,Name,Mail_Id,Marks,Teacher";
    // File column header values
    public String[] headerTags = {"Roll No","Name","Mail_Id","Marks","Teacher"};
    // stores if the current user is CC
    public boolean isCC = false;
    // stores if the current user is TA
    public boolean isTA = false;
    // stores if the TA is TA1 or TA2
    public int TA_id;

    // Reads the 'Stud_info.txt' file and returns the data as a ArrayList
    public ArrayList<String> readFile() throws IOException{
        // structure to store the data from the file
        ArrayList<String> dataRows = new ArrayList<String>();
        // Get the path of the file
        Path filepath = Paths.get(System.getProperty("user.dir") + "/Stud_info.txt");
        // Open the file in 'READ' mode
        FileChannel fileChannel = FileChannel.open(filepath, StandardOpenOption.READ);
        // Put a 'SHARED LOCK' on the complete file while reading the file
        // This prevents any other user from writing to the file but other users
        // can read from the file at the same time using shared lock
        FileLock lock = fileChannel.lock(0, Long.MAX_VALUE, true);
        
        // Allocate buffer equal to file size to read the file contents
        ByteBuffer buffer = ByteBuffer.allocate((int)fileChannel.size());
        // read the file into buffer
        fileChannel.read(buffer);
        buffer.flip();
        String row = "";
        // Split the files into rows since each row is a separate record entry
        for(int i=0;i<fileChannel.size();i++){
            // get next character from buffer
            char c = (char)buffer.get();
            // if newline character is seen
            if(c=='\n'){
                // add the 'row' string to dataRow as a separate record
                dataRows.add(row);
                row = "";
                continue;
            }
            row += c;
        }
        // close the file and release the lock
        fileChannel.close();
        // remove the header columns from the read data
        if(dataRows.size()>0){
            dataRows.remove(0);
        }
        //return the data
        return dataRows;
    } 
    
    // Write data to file exclusively
    public void updateFile (ArrayList<String> dataRows,String filename) throws IOException{
        // Get the path to the file
        Path filepath = Paths.get(System.getProperty("user.dir") + "/" + filename);
        // Open the file in write mode
        FileChannel fileChannel = FileChannel.open(filepath,StandardOpenOption.WRITE,StandardOpenOption.TRUNCATE_EXISTING);
        // Put a 'EXCLUSIVE LOCK' on the file. This prevent any other user to write
        // or read from the file until the current user releases the lock
        FileLock lock = fileChannel.lock();
        // move the cursor to the start of file to start writing fresh data
        fileChannel.position(0);
        // Create a buffer containg the header columns
        ByteBuffer buffer = ByteBuffer.wrap((header+"\n").getBytes());
        // Write the data from buffer to the file
        fileChannel.write(buffer);
        // Iteratively write each record into the file
        for(int i=0;i<dataRows.size();i++){
            buffer = ByteBuffer.wrap((dataRows.get(i)+"\n").getBytes());
            fileChannel.write(buffer);
        }
        // Close the file and release the lock
        fileChannel.close();
    }

    // Function calls updateFile to write to each file one by one
    public void updateFiles(ArrayList<String> dataRows) throws IOException{
        // write the data to 'Stud_info.txt'
        updateFile(dataRows,"Stud_info.txt");

        // Sort the data based on roll np.
        Collections.sort(dataRows, new Comparator<String>() {
            @Override
            public int compare(String arg0, String arg1) {
                return arg0.split(",")[0].compareTo(arg1.split(",")[0]);
            }
        });
        // write the sorted data to 'Sorted_roll.txt'
        updateFile(dataRows, "Sorted_roll.txt");

        // Sort the data on name
        Collections.sort(dataRows, new Comparator<String>() {
            @Override
            public int compare(String arg0, String arg1) {
                return arg0.split(",")[1].toUpperCase().compareTo(arg1.split(",")[1].toUpperCase());
            }
        });
        // write the sorted data to 'Sorted_name.txt'
        updateFile(dataRows, "Sorted_name.txt");
    }

    // Functions takes user input to update various fields of a record
    public String[] getUpdatedValues(String[] row) throws IOException{
        // initialise a scanner to read user input
        Scanner S = new Scanner(System.in);
        // Initialise empty record with 5 columns each corresponding to a single column in file
        String[] record = new String[5];

        // Display message to user
        System.out.println("Type new value to update or press Enter to keep same :");
        
        // For each column ask for user to input new data or keep the field same as original value
        for(int i=0;i<4;i++){
            System.out.println(headerTags[i] + " : (previous value = " + row[i] + ")");
            String value = S.nextLine().trim();
            // If user did not enter anything, keep the field value as the last stored value
            if(!value.equals("")){
                record[i] = value;
            }
            // else update the field
            else{
                record[i] = row[i];
            }
        }
        // if the current user is CC, update the teacher field to CC for current record
        if(isCC){
            record[4] = "CC";
        }
        // if the current user is TA
        else{
            // TA1, update the teacher field to TA1 for current record
            if(TA_id==1){
                record[4] = "TA1";
            }
            // TA2, update the teacher field to TA2 for current user
            else{
                record[4] = "TA2";
            }
        }
        // return the updated record
        return record;
    }

    // Function adds a new record entry
    public void addRecord() throws IOException{
        // Initialise a new record consisting of 5 fields
        String[] record = new String[5];
        // Initialise a scanner to read user input
        Scanner S = new Scanner(System.in);
        
        // Ask for values of each field
        for(int i=0;i<4;i++){
            System.out.println("Enter " + headerTags[i] + " : ");
            record[i] = S.nextLine().trim();
        }

        // if current user is CC, update teacher field for new record to CC
        if(isCC){
            record[4] = "CC";
        }
        // if current user is TA
        else{
            // TA1, update teacher field for new record to TA1
            if(TA_id==1){
                record[4] = "TA1";
            }
            // TA2, update teacher field for new record to TA2
            else{
                record[4] = "TA2";
            }
        }

        // Retrieve previous data from the file
        ArrayList<String> dataRows = readFile();
        String[] row;
        // check for each record in the file
        for(int i=0;i<dataRows.size();i++){
            row = dataRows.get(i).split(",");
            // if any record has same roll no as the new record
            if(row[0].equals(record[0])){
                // SHow error message and cancel adding new record
                System.out.println("Record already exists. Try editing the record");
                return;
            }
        }
        // add the new record to the existing records list
        dataRows.add(String.join(",", record));
        // write the new data to all the files
        updateFiles(dataRows);
    }

    // Function updates fields of already existing record from the file
    public void updateRecord() throws IOException{
        // initialise a scanner to read user input
        Scanner S = new Scanner(System.in);
        // Ask the user for roll no of the student whose details have to be updated
        System.out.println("Enter Roll No of record to be updated : ");
        String rollNo = S.nextLine().trim();

        // Read the file to retrieve already existing record
        ArrayList<String> dataRows = readFile();
        String[] row;
        boolean readyToUpdate = false;
        // Search the existing records for the roll no of student provided by user
        for(int i=0;i<dataRows.size();i++){
            row = dataRows.get(i).split(",");
            if(row[0].equals(rollNo)){
                // If the current user can update the record, proceed
                if(isCC || row[4]==null || row[4].equals("") || row[4].startsWith("TA")){
                    readyToUpdate = true;
                    // get the updated values for the record fields by the user
                    String[] record = getUpdatedValues(row);
                    // change the values in the list of records
                    dataRows.set(i,String.join(",",record));
                }
                // If user does not have permissions to edit the record, show error message
                else{
                    System.out.println("Permission denied for editing the record");
                }
                // break out of for loop
                break;
            }
        }
        // If the record can be updated, write the updated details to all the files
        if(readyToUpdate){
            updateFiles(dataRows);
        }
    }

    // Function to view the record
    public void viewRecord() throws IOException{
        Scanner S = new Scanner(System.in);
        System.out.println("Enter Roll No of record to view : ");
        // Get user input for roll no of the queried record
        String rollNo = S.nextLine().trim();

        // Retrieve all the records from the file
        ArrayList<String> dataRows = readFile();
        String[] row = new String[5];
        boolean recordFound = false;
        // For each record match the roll of the record with the user-input roll no
        for(int i=0;i<dataRows.size();i++){
            row = dataRows.get(i).split(",");
            // if roll np matches
            if(row[0].equals(rollNo)){
                recordFound = true;
                break;
            }
        }
        // If record is found in the file
        if(recordFound){
            // Output the field values for the record to user
            for(int i=0;i<5;i++){
                System.out.println(headerTags[i] + " : " + row[i]);
            }
        }
        // If record not found, display error messgae
        else{
            System.out.println("No record Found for Roll No : " + rollNo);
        }
    }

    // Start Page for selection various options
    public void startPage() throws IOException{
        // true until user exits
        boolean loggedIn = true;
        // scanner to read user option choice
        Scanner S = new Scanner(System.in);

        while(loggedIn){
            // Enter details of how to choose the options
            System.out.println("Enter the number corresponding to the choice :");
            System.out.println("1 Add New Record\n2 Edit existing record\n3 View record\n4 Exit");
            // Get the user choice and call appropriate function according to user choice
            int choice = S.nextInt();
            switch(choice){
                case 1:
                    addRecord();
                    break;
                case 2:
                    updateRecord();
                    break;
                case 3:
                    viewRecord();
                    break;
                case 4:
                    // if user chooses exit, set loogenIn to false
                    loggedIn = false;
                    break;
            }
        }
    }
    // Main function to start execution of program
    public static void main(String[] args) throws IOException{
        // Check if the text file already exists
        // If not create new empty file with the given name
        String dirPath = System.getProperty("user.dir") + "/";

        File file;
        
        //Stud_info.txt
        file = new File(dirPath+"Stud_info.txt");
        if(!file.exists()){
            file.createNewFile();
        }

        //Sorted_roll.txt
        file = new File(dirPath+"Sorted_roll.txt");
        if(!file.exists()){
            file.createNewFile();
        }

        //Sorted_name.txt
        file = new File(dirPath+"Sorted_name.txt");
        if(!file.exists()){
            file.createNewFile();
        }

        // create an object of main class
        dataModification dm = new dataModification();
        Scanner S = new Scanner(System.in);
        // Ask for user designation
        System.out.println("Enter the number corresponding to the user-type : ");
        System.out.println("1 CC\n2 TA1\n3 TA2");
        // Get user designation choice
        int choice = S.nextInt();
        switch(choice){
            case 1:
                dm.isCC = true;
                break;
            case 2:
                dm.isTA = true;
                dm.TA_id = 1;
                break;
            case 3:
                dm.isTA = true;
                dm.TA_id = 2;
                break;
            default:
                System.out.println("Invalid choice");
                return;
        }
        // Proceed furthur
        dm.startPage();
    }
}
