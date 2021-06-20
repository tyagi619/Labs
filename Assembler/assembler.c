#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

//variable to store the address
unsigned int LOCCTR = 0X0000;
int flag=-1;
//Stores the machine code for given opcode
char machine_code[12][128];
//Check if a operand has been written to optable.txt or not
int MachineCodeUsed[12]={0};
//Function Declaration
void split(char *str);
void split4(char *str);
void HexToBin(char *hexdec,char *binary); 
void decToBinary(char *binary,int decimal,int bits);
void WriteToSymTable(char *label);
void GetLabelAddress(char *label,char *address);
void InsertNewline();
void WriteToOptable(char *opcode,int index);
void WriteToOutput(int index);
void string_toUpper(char *str);
void Read_Opcode_from_File();
int increment_memory(char *val,int k);
int PROCESS_OPCODE(char *line, char *opcode, char *val1 , char *val2,int k);
int min_val(int a){
    return a==-1?0:1;
}

int main(){
    Read_Opcode_from_File();
    //Declare file pointers for the input asm file, symbol table file and opcode table file
    FILE *fp_code,*fp_opcode,*fp_symbol,*fp_output;
    //Specify the file names and mode of operation for each file
    fp_code = fopen("input.asm" , "r");
    fp_symbol = fopen("symTable.txt" , "w");
    fp_opcode  = fopen("opTable.txt" , "w");
    //test if file is succesfully opened
    if(fp_code == NULL || fp_opcode == NULL || fp_symbol == NULL){
        printf("The input file could not be opened\n");
        return 0;
    }
    fputs("Opcode      Machine Code\n",fp_opcode);
    fputs("",fp_symbol);
    fclose(fp_opcode);
    fclose(fp_symbol);
    //Character array for storing the line read from input.asm file
    char line[128];
    //Character array for storing opcode read
    char opcode[128];
    //Stores the operands
    char val1[128];
    char val2[128];
    //Pass 1
    //Read input line by line
    while(fgets(line, sizeof line, fp_code) != NULL){
        //Initialise opcode to empty character array
        opcode[0] = '\0';
        //Read opcode from the current line
        sscanf(line,"%s",opcode);
        //If opcode is empty character array , the line does not contain any opcode and continue in this case
        if(opcode[0] == '\0'){
            continue;
        }
        //Convert opcode and line read to Uppercase
        string_toUpper(opcode);
        string_toUpper(line);
        //Initialise opreands to empty string
        val1[0] = '\0';
        val2[0] = '\0';
        //Permorms operation according to the opcode and increments address counter accordingly
        if(!PROCESS_OPCODE(line,opcode,val1,val2,0)){
            break;
        }
    }
    //CLose all open files
    fclose(fp_code);
    //Pass2 starts
    //Initialise memory counter to 0X0000
    LOCCTR = 0X0000;
    //Open input.asm
    fp_code = fopen("input.asm" , "r");
    //Open output.o file
    fp_output = fopen("output.o" , "w");
    //Clear the contents of instruction file if file exists and has some content written in it
    fputs("",fp_output);
    //Close the file output.o
    fclose(fp_output);
    flag=-1;
    //Read from input.asm line by line
    while(fgets(line, sizeof line, fp_code) != NULL){
        //Initialise opcode to empty string
        opcode[0] = '\0';
        //Read the opcode from the current line
        sscanf(line,"%s",opcode);
        if(opcode[0] == '\0'){
            continue;
        }
        //Convert opcode and line read to uppercase
        string_toUpper(opcode);
        string_toUpper(line);
        val1[0] = '\0';
        val2[0] = '\0';
        //Performs operation according to the opcode
        if(!PROCESS_OPCODE(line,opcode,val1,val2,min_val(flag))){
            break;
        }
    }
    //Close input.asm
    fclose(fp_code);
    return 0;

}
//Performs operations according to opcode value
//During pass 1 assigns address to each line
//During pass 2 writes the line address and opcode value to output.o
int PROCESS_OPCODE(char *line , char *opcode, char *val1 , char *val2 , int k){
    char temp[128];
    if(!strcmp(opcode,"START")){  //If opcode is start continue
        LOCCTR = 0X0000;
        flag=1;
        return 1;
    }
    if(flag!=1){
        return 1;
    }
    if(!strcmp(opcode,"ADD")){ // If opcode is ADD
        //Read the operands
        sscanf(line,"%*s %[^,] , %s",temp,val2);
        sscanf(temp,"%s",val1);
        if(k==0){
            //Write the opcode and its machine code to the opTable.txt if it is used for the first time
            if(!MachineCodeUsed[1]){
                WriteToOptable(opcode,1);
            }
        }
        else{
            //Write the address of line along with machine code for the opcode in output.o
            WriteToOutput(1);
        }
        //Increment the LOCCTR according to the operand types
        int ctr = 4;
        ctr+=increment_memory(val1,k);
        ctr+=increment_memory(val2,k);
        //Insert newline in output.o
        if(k==1){
            InsertNewline();    
        }
        LOCCTR += (ctr+7)/8;
        return 1;
    }
    else if(!strcmp(opcode,"SUB")){ //If opcode is SUB
        //Read the operands        
        sscanf(line,"%*s %[^,] , %s",temp,val2);
        sscanf(temp,"%s",val1);
        if(k==0){
            //Write the opcode and its machine code to the opTable.txt if it is used for the first time
            if(!MachineCodeUsed[2]){
                WriteToOptable(opcode,2);
            }
        }
        else{
            //Write the address of line along with machine code for the opcode in output.o
            WriteToOutput(2);
        }
        //Increment the LOCCTR according to the operand types
        int ctr = 4;
        ctr+=increment_memory(val1,k);
        ctr+=increment_memory(val2,k);
        //Insert newline in output.o
        if(k==1){
            InsertNewline();    
        }
        LOCCTR += (ctr+7)/8;
        return 1;
    }
    else if(!strcmp(opcode,"MUL")){// If opcode is MUL
        //Read the operand
        sscanf(line,"%*s %s",val1);
        if(k==0){
            //Write the opcode and its machine code to the opTable.txt if it is used for the first time
            if(!MachineCodeUsed[3]){
                WriteToOptable(opcode,3);
            }
        }
        else{
            //Write the address of line along with machine code for the opcode in output.o
            WriteToOutput(3);
        }
        int ctr = 4;
        if(k==1){
            FILE *fp_output;
            fp_output = fopen("output.o","a");
            fputs("00001 ",fp_output);
            fclose(fp_output); 
        }
        ctr+=increment_memory(val1,k);
        if(k==1){
            InsertNewline();    
        }
        LOCCTR += (ctr+7)/8;
        return 1;
    }
    else if(!strcmp(opcode,"MOV")){
        sscanf(line,"%*s %[^,] , %s",temp,val2);
        sscanf(temp,"%s",val1);
        if(k==0){
            //Write the opcode and its machine code to the opTable.txt if it is used for the first time
            if(!MachineCodeUsed[0]){
                WriteToOptable(opcode,0);
            }
        }
        else{
            //Write the address of line along with machine code for the opcode in output.o
            WriteToOutput(0);
        }
        int ctr = 4;
        ctr+=increment_memory(val1,k);
        ctr+=increment_memory(val2,k);
        if(k==1){
            InsertNewline();    
        }
        LOCCTR += (ctr+7)/8;
        return 1;
    }
    else if(!strcmp(opcode,"CMP")){
        sscanf(line,"%*s %[^,] , %s",temp,val2);
        sscanf(temp,"%s",val1);
        if(k==0){
            //Write the opcode and its machine code to the opTable.txt if it is used for the first time
            if(!MachineCodeUsed[4]){
                WriteToOptable(opcode,4);
            }
        }
        else{
            //Write the address of line along with machine code for the opcode in output.o
            WriteToOutput(4);
        }
        int ctr = 4;
        ctr+=increment_memory(val1,k);
        ctr+=increment_memory(val2,k);
        if(k==1){
            InsertNewline();    
        }
        LOCCTR += (ctr+7)/8;     
        return 1;
    }
    else if(!strcmp(opcode,"AND")){
        sscanf(line,"%*s %[^,] , %s",temp,val2); 
        sscanf(temp,"%s",val1);
        if(k==0){
            //Write the opcode and its machine code to the opTable.txt if it is used for the first time
            if(!MachineCodeUsed[5]){
                WriteToOptable(opcode,5);
            }
        }
        else{
            //Write the address of line along with machine code for the opcode in output.o
            WriteToOutput(5);
        }
        int ctr = 4;
        ctr+=increment_memory(val1,k);
        ctr+=increment_memory(val2,k);
        if(k==1){
            InsertNewline();    
        }
        LOCCTR += (ctr+7)/8;
        return 1;
    }
    else if(!strcmp(opcode,"OR")){
        sscanf(line,"%*s %[^,] , %s",temp,val2);
        sscanf(temp,"%s",val1);
        if(k==0){
            //Write the opcode and its machine code to the opTable.txt if it is used for the first time
            if(!MachineCodeUsed[6]){
                WriteToOptable(opcode,6);
            }
        }
        else{
            //Write the address of line along with machine code for the opcode in output.o
            WriteToOutput(6);
            
        }
        int ctr = 4;
        ctr+=increment_memory(val1,k);
        ctr+=increment_memory(val2,k);
        if(k==1){
            InsertNewline();    
        }
        LOCCTR += (ctr+7)/8; 
        return 1;
    }
    else if(!strcmp(opcode,"NOT")){
        sscanf(line,"%*s %s",val1);
        if(k==0){
            //Write the opcode and its machine code to the opTable.txt if it is used for the first time
            if(!MachineCodeUsed[7]){
                WriteToOptable(opcode,7);
            }
        }
        else{
            //Write the address of line along with machine code for the opcode in output.o
            WriteToOutput(7);
        }
        int ctr = 4;
        ctr+=increment_memory(val1,k);
        if(k==1){
            InsertNewline();    
        }
        LOCCTR += (ctr+7)/8;;
        return 1;
    }
    else if(!strcmp(opcode,"JMP")){
        if(k==0){
            //Write the opcode and its machine code to the opTable.txt if it is used for the first time
            if(!MachineCodeUsed[8]){
                WriteToOptable(opcode,8);
            }
        }
        else{
            //Write the address of line along with machine code for the opcode in output.o
            WriteToOutput(8);

            FILE *fp_output;
            char sub[128],address[128];
            sscanf(line,"%*s %s",sub);
            string_toUpper(sub);
            //Get address of label from symTable.txt
            GetLabelAddress(sub,address);
            char binary[128];
            HexToBin(address,binary);
            //Split the string at 8 bits
            long long int value_16bit_binary;  
            sscanf(binary,"%lld",&value_16bit_binary);
            sprintf(binary,"%016lld ",value_16bit_binary);
            split4(binary);
            //Write the address of label to output.o
            fp_output = fopen("output.o","a");
            fprintf(fp_output, "%s ",binary);
            fclose(fp_output);
            InsertNewline();
        }
        //Increment LOCCTR by 3
        LOCCTR += 3;
        return 1;
    }
    else if(!strcmp(opcode,"HLT")){//If opcode is HLT
        if(k==0){
            //Write the opcode and its machine code to the opTable.txt if it is used for the first time
            if(!MachineCodeUsed[10]){
                WriteToOptable(opcode,10);
            }
        }
        else{
            //Write the address of line along with machine code for the opcode in output.o
            WriteToOutput(10);
            InsertNewline();
        }
        LOCCTR += 1;
        return 1;
    }
    else if(!strcmp(opcode,"JNZ")){ //if Opcode is JNZ
        if(k==0){
            //Write the opcode and its machine code to the opTable.txt if it is used for the first time
            if(!MachineCodeUsed[11]){
                WriteToOptable(opcode,11);
            }
        }
        else{
            //Write the address of line along with machine code for the opcode in output.o
            WriteToOutput(11);

            FILE *fp_output;
            char sub[128],address[128];
            sscanf(line,"%*s %s",sub);
            string_toUpper(sub);
            //Get the address of label from symTable.txt
            GetLabelAddress(sub,address);
            char binary[128];
            HexToBin(address,binary);
            //Split the string at 8 bits
            long long int value_16bit_binary;  
            sscanf(binary,"%lld",&value_16bit_binary);
            sprintf(binary,"%016lld ",value_16bit_binary);
            split4(binary);

            //Write the address of label to output.o
            fp_output = fopen("output.o","a");
            fprintf(fp_output, "%s ",binary);
            fclose(fp_output);
            InsertNewline();
        }
        //Increase LOCCTR by 3 
        LOCCTR += 3;
        return 1;
    }
    else if(!strcmp(opcode,"END")){ // If opcode is END
        //End the file reading
        return 0;
    }
    else if(!strcmp(opcode,"LOOP")){
        //Loop comprises of 2 opcodes : SUB and JNZ
        if(k==0){
            //If SUB hasn't been used before, write opcode to opTable.txt 
            if(!MachineCodeUsed[2]){
                WriteToOptable("SUB\0",2);
            }
            //If JNZ hasn't been used before, write opcode to opTable.txt
            if(!MachineCodeUsed[11]){
                WriteToOptable("JNZ\0",11);
            }
            //Increase LOCCTR By 7
            LOCCTR += 7;
        }
        else{
            FILE *fp_output;
            //SUB
            //Write the address of line along with machine code for the opcode in output.o
            WriteToOutput(2);
            //Subtract 1 from the counter register (R31)
            //Write the operands for SUB instruction in output.o
            fp_output = fopen("output.o","a");
            fputs("11111 00000000 00000001",fp_output);
            fclose(fp_output);
            InsertNewline();

            LOCCTR+=4;
            //JNZ 
            //Write the address of line along with machine code for the opcode in output.o
            WriteToOutput(11);

            char sub[128],address[128];
            sscanf(line,"%*s %s",sub);
            string_toUpper(sub);
            //Get the address of the label from symTable.txt
            GetLabelAddress(sub,address);
            char binary[128];
            HexToBin(address,binary);
            //Split the string at 8 bits
            long long int value_16bit_binary;  
            sscanf(binary,"%lld",&value_16bit_binary);
            sprintf(binary,"%016lld ",value_16bit_binary);
            split4(binary);
            //Write the address of label to output.o
            fp_output = fopen("output.o","a");
            fprintf(fp_output, "%s ",binary);
            fclose(fp_output);
            InsertNewline();

            LOCCTR+=3;
        }
        return 1;
    }
    else{//It is a label or a comment
        if(opcode[0] == ';'){ //Ignore comments
            return 1;
        }
        //Process the labels
        int len = strlen(opcode);
        char label[128]; //Stores label name

        if(opcode[len-1]==':'){
            sscanf(opcode,"%[^:]",label);
        }
        else{
            strcpy(label,opcode);
        }
        string_toUpper(label);
        if(k==0 && flag==1){
            //Write the label name along with its line address to symTable.txt
            WriteToSymTable(label);
        }

        char instruction[128];
        //Read the instruction after the label name if any
        if(sscanf(line,"%*[^:] : %[^\n]",instruction) == 1){
            char sub_opcode[128];
            //get the opcode for the instruction
            sscanf(instruction,"%s",sub_opcode);
            string_toUpper(sub_opcode);
            char sub_val1[128],sub_val2[128];
            //Character array for storing operands
            sub_val1[0] = '\0';
            sub_val2[0] = '\0';
            return PROCESS_OPCODE(instruction,sub_opcode,sub_val1,sub_val2,k);
        }
        return 1;
    }
}
//increments memory according to operand type 
//During pass 2 writes the operand values to output.o
//Returns the number of bits occupied by each operand
int increment_memory(char *val,int k){
    int len = strlen(val);
    int ctr = 0;
    if(toupper(val[len-1])=='H'){ //Check if number is hexadecimal
        ctr+=16;
        if(k==1){
            char sub[128];
            char binary[128];

            strncpy(sub, val, len-1); //Get hexadecimal number
            sub[len-1] = '\0';
            HexToBin(sub,binary);   //Convert to binary 
            //Split the string at 8th bit
            long long int value_16bit_binary;  
            sscanf(binary,"%lld",&value_16bit_binary);
            sprintf(binary,"%016lld ",value_16bit_binary);
            split(binary);
            //Write to output.o
            FILE *fp_output;
            fp_output = fopen("output.o","a");
            fprintf(fp_output,"%s ",binary);
            fclose(fp_output);
        }
    }
    else if(val[0] >= '0' && val[len-1] >= '0' && val[0] <= '9' && val[len-1] <= '9'){ //If number is hexadecimal
        ctr+=16;
        if(k==1){
            char sub[128];
            char binary[128];

            strncpy(sub, val, len); //Get hexadecimal number
            sub[len] = '\0';
            HexToBin(sub,binary);   //Convert to binary 
            //Split the string at 8th bit
            long long int value_16bit_binary;  
            sscanf(binary,"%lld",&value_16bit_binary);
            sprintf(binary,"%016lld ",value_16bit_binary);
            split(binary);
            //Write to output.o
            FILE *fp_output;
            fp_output = fopen("output.o","a");
            fprintf(fp_output,"%s ",binary);
            fclose(fp_output);
        }
    }
    else if(toupper(val[len-1])=='B'){//Check if number is binary
        ctr+=16;
        if(k==1){
            char sub[128];
            strncpy(sub, val, len-1);
            sub[len-1] = '\0';
            //Split the string at 8th bit
            long long int value_16bit_binary;
            sscanf(sub,"%lld",&value_16bit_binary);//Get the binary number
            sprintf(sub,"%016lld ",value_16bit_binary);
            split(sub);
            //Write to output.o
            FILE *fp_output;                  //Write to output.o
            fp_output = fopen("output.o","a");
            fprintf(fp_output, "%s ",sub);
            fclose(fp_output);
        }
    }
    else if(toupper(val[len-1])=='D'){//Check if number is decimal
        ctr+=16;
        
        if(k==1){
            char sub[128];
            strncpy(sub, val, len-1);
            sub[len-1] = '\0';
            //Split the string at 8th bit
            int decimal;
            char binary[128];
            sscanf(sub,"%d",&decimal);//Get the value of the number
            decToBinary(binary,decimal,16);//Convert to binary
            split(binary);
            //Write to output.o
            FILE *fp_output;         //Write to output.o
            fp_output = fopen("output.o","a");
            fprintf(fp_output, "%s ",binary);
            fclose(fp_output);
        }
    }
    else{ // the value is for a register
        ctr += 5;
        if(k==1){
            char sub[128];
            int register_number;
            char binary[6];
            sscanf(val,"%*[^0-9] %d",&register_number); //Get the register number
            decToBinary(binary,register_number,5); //Convert decimal to binary
            //Write to output.o
            FILE *fp_output;
            fp_output = fopen("output.o","a");
            fprintf(fp_output, "%s ",binary);
            fclose(fp_output);
        }
    }
    return ctr;
}
//Writes the label name and its address to symTable.txt
void WriteToSymTable(char *label){
    FILE *fp_symbol;
    fp_symbol = fopen("symTable.txt" , "a");
    fprintf(fp_symbol, "%s: %04XH\n",label,LOCCTR);
    fclose(fp_symbol);    
}
//Writes the opcode and corresponding machine code for it in optable.txt
void WriteToOptable(char *opcode, int index){
    FILE *fp_optable;
    fp_optable = fopen("opTable.txt" , "a");
    fprintf(fp_optable, "%s         %s\n",opcode,machine_code[index]);
    fclose(fp_optable);
    MachineCodeUsed[index] = 1;
}
//writes the line address and the machine code for the opcode in output.o
void WriteToOutput(int index){
    FILE *fp_output;
    fp_output = fopen("output.o","a");
    fprintf(fp_output, "%04X       %s ",LOCCTR,machine_code[index]);
    fclose(fp_output);
}
//Gets the address of label from symTable.txt
void GetLabelAddress(char *label,char *address){
    char line[128],stored_label[128];
    FILE *fp_symbol;
    fp_symbol = fopen("symTable.txt","r");
    //Read the file line by line
    while(fgets(line, sizeof line , fp_symbol) != NULL){
        sscanf(line,"%[^:] : %[^H]",stored_label,address);
        if(!strcmp(label,stored_label)){ //Check if the read value is same as label name
            fclose(fp_symbol);
            return;
        }
    }
    fclose(fp_symbol);
}
//Inserts newline character in output.o 
void InsertNewline(){
    FILE *fp_output;
    fp_output = fopen("output.o","a");
    fputs("\n",fp_output);
    fclose(fp_output);
}
//Reads the opcode and corresponding machine code from file and stores the result
void Read_Opcode_from_File(){
    FILE *fp_machineCode;
    fp_machineCode = fopen("opcode.txt","r");
    if(fp_machineCode == NULL){
        printf("File not found\n");
        return;
    }
    char line[128];
    char opcode[128];
    while(fgets(line,sizeof line,fp_machineCode) != NULL){
        sscanf(line,"%s",opcode);
        if(!strcmp(opcode,"MOV")){
            sscanf(line,"%*s %s",machine_code[0]);
        }
        else if(!strcmp(opcode,"ADD")){
            sscanf(line,"%*s %s",machine_code[1]);
        }
        else if(!strcmp(opcode,"SUB")){
            sscanf(line,"%*s %s",machine_code[2]);
        }
        else if(!strcmp(opcode,"MUL")){
            sscanf(line,"%*s %s",machine_code[3]);
        }
        else if(!strcmp(opcode,"CMP")){
            sscanf(line,"%*s %s",machine_code[4]);
        }
        else if(!strcmp(opcode,"AND")){
            sscanf(line,"%*s %s",machine_code[5]);
        }
        else if(!strcmp(opcode,"OR")){
            sscanf(line,"%*s %s",machine_code[6]);
        }
        else if(!strcmp(opcode,"NOT")){
            sscanf(line,"%*s %s",machine_code[7]);
        }
        else if(!strcmp(opcode,"JMP")){
            sscanf(line,"%*s %s",machine_code[8]);
        }
        else if(!strcmp(opcode,"LOOP")){
            sscanf(line,"%*s %s",machine_code[9]);
        }
        else if(!strcmp(opcode,"HLT")){
            sscanf(line,"%*s %s",machine_code[10]);
        }
        else if(!strcmp(opcode,"JNZ")){
            sscanf(line,"%*s %s",machine_code[11]);
        }
    }
    fclose(fp_machineCode);
}
//Converts the string to uppercase
void string_toUpper(char *str){
    int i=0;
    while(str[i]!='\0'){
        str[i] = toupper(str[i]);
        i++;
    }
    return;
}
//Converts hexadecimal number to 16 bit binary
void HexToBin(char *hexdec,char *binary) { 
   int i=0;
   int j=0; 
  
    while (hexdec[i]!='\0') { 
  
        switch (hexdec[i]) { 
        case '0': 
            binary[j]='0';
            binary[j+1] = '0';
            binary[j+2] = '0';
            binary[j+3] = '0'; 
            break; 
        case '1': 
            binary[j]='0';
            binary[j+1] = '0';
            binary[j+2] = '0';
            binary[j+3] = '1';  
            break; 
        case '2': 
            binary[j]='0';
            binary[j+1] = '0';
            binary[j+2] = '1';
            binary[j+3] = '0'; 
            break; 
        case '3': 
            binary[j]='0';
            binary[j+1] = '0';
            binary[j+2] = '1';
            binary[j+3] = '1';  
            break; 
        case '4': 
            binary[j]='0';
            binary[j+1] = '1';
            binary[j+2] = '0';
            binary[j+3] = '0'; 
            break; 
        case '5': 
            binary[j]='0';
            binary[j+1] = '1';
            binary[j+2] = '0';
            binary[j+3] = '1';  
            break; 
        case '6': 
            binary[j]='0';
            binary[j+1] = '1';
            binary[j+2] = '1';
            binary[j+3] = '0';  
            break; 
        case '7': 
            binary[j]='0';
            binary[j+1] = '1';
            binary[j+2] = '1';
            binary[j+3] = '1';  
            break; 
        case '8': 
            binary[j]='1';
            binary[j+1] = '0';
            binary[j+2] = '0';
            binary[j+3] = '0';  
            break; 
        case '9': 
            binary[j]='1';
            binary[j+1] = '0';
            binary[j+2] = '0';
            binary[j+3] = '1'; 
            break; 
        case 'A': 
        case 'a': 
            binary[j]='1';
            binary[j+1] = '0';
            binary[j+2] = '1';
            binary[j+3] = '0'; 
            break; 
        case 'B': 
        case 'b': 
            binary[j]='1';
            binary[j+1] = '0';
            binary[j+2] = '1';
            binary[j+3] = '1';  
            break; 
        case 'C': 
        case 'c': 
            binary[j]='1';
            binary[j+1] = '1';
            binary[j+2] = '0';
            binary[j+3] = '0'; 
            break; 
        case 'D': 
        case 'd': 
            binary[j]='1';
            binary[j+1] = '1';
            binary[j+2] = '0';
            binary[j+3] = '1';  
            break; 
        case 'E': 
        case 'e': 
            binary[j]='1';
            binary[j+1] = '1';
            binary[j+2] = '1';
            binary[j+3] = '0';  
            break; 
        case 'F': 
        case 'f': 
            binary[j]='1';
            binary[j+1] = '1';
            binary[j+2] = '1';
            binary[j+3] = '1';  
            break; 
        } 
        i++;
        j+=4; 
    }
    binary[j]='\0'; 
} 
//Converts decimal number to n bit binary number
void decToBinary(char *binary,int decimal,int bits) {  
    char temp[bits];
    // counter for binary array 
    int i = 0; 
    //Calculate the binary number
    while (decimal > 0) { 
        temp[i] = 48 + (decimal % 2);
        decimal = decimal / 2; 
        i++; 
    } 
    //Copy the binary number to binary character array
    for(int j=0;j<i;j++){
        binary[j+bits-i] = temp[i-j-1];
        // printf("%c %d\n",temp[j-bits+i],j );
    }
    //Fill the leftover bits by 0
    for(int j=0;j<bits-i;j++){
        binary[j] = '0';
        // printf("%c\n",bits[i] );
    }
    binary[bits] = '\0';
} 
//Splits the string at 8 bits
void split(char *str){
    char tmp1[10] = "",tmp2[10] = "";
    strncpy(tmp1, str, 8);
    strncpy(tmp2, str+8, 8);
    sprintf(str, "%s %s", tmp1,tmp2);
}
//Splits the string into 4 equal parts
void split4(char *str){
    char tmp1[10] = "",tmp2[10] = "",tmp3[10] = "",tmp4[10]="";
    strncpy(tmp1, str, 4);
    strncpy(tmp2, str+4, 4);
    strncpy(tmp3, str+8, 4);
    strncpy(tmp4, str+12, 4);
    sprintf(str, "%s %s %s %s", tmp1,tmp2,tmp3,tmp4);
}