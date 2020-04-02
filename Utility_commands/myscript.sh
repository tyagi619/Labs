#! /bin/bash

#ECHO COMMAND
echo "Hello World!"

#VARIABLES
#uppercase by convention
#Letters, numbers, underscores


#NAME = "Anubhav" is incorrect
NAME="Anubhav"
echo "My name is $NAME"
echo "My name is ${NAME}"

#User Input
#read -p "Enter your name: "NAME1 will not accept any argument
read -p "Enter your name: " NAME1   #takes user input
echo "Hello $NAME1 , Nice to meet you"

#Simple if statement
if [ "$NAME1" == "Anubhav" ] 
then
	echo "Access Denied"
elif [ "$NAME1" == "Manan" ]
then
	echo "Calling the cops"	
else
	echo "Welcome $NAME1"	
fi

#Comparison
# -eq equal to
# -ne not equal to
# -gt greater than
# -ge greater than or equal to
# -lt less than
# -le less than or equal to

NUM1=3
NUM2=5
if [ "$NUM1" -gt "$NUM2" ]
then
	echo "$NUM1"
else
	echo "$NUM2"
fi

#FILE CONDITIONS
# -d file  True if the file is a directory
# -e file  True if the file exists (note that this is not particularly portable, thus -f is generally used)
# -f file  True if the provided string is a file
# -g file  True if the group id is set on a file
# -r file  True if the file is readable	
# -u  True if the user id is set on a file type
# -w  True if the file is writable
# -x  True if the file is an executable 
########### 	

FILE="test.txt"
if [ -f "$FILE" ]
then 
	#touch file.txt
	echo "$FILE is a file"
elif [ -d "$FILE" ]
then
	#rm file.txt;mkdir file.txt
	echo "$FILE is a directory"
elif [ -e "$FILE" ]
then
	echo "$FILE exists"		
else
	echo "$FILE is NOT  a file"
fi	


#CASE STATEMENT
read -p "Are you over 18? Y/N" ANSWER
case "$ANSWER" in
	[yY] | [yY][eE][sS])
		echo "You can have beer :)"
		;;
	[Nn] | [Nn][oO])	
		echo "Feel free to have a soft drink :("
		;;
	*)
		echo "Please enter y/yes or n/no"
		;;
esac 			



#SIMPLE FOR LOOP
NAMES="Manan Anubhav Abhishek Ravi"
for NAME in $NAMES
	do
		echo "Hello $NAME !!!"
done

#FOR LOOP TO RENAME FILES
FILES=$(ls *.txt)
NEW="new"
for FILE in $FILES
	do
		echo "Renaming $FILE to new-$FILE"
		mv $FILE $NEW-$FILE
done		
					

#WHILE LOOP - READ THROUGH A FILE LINE BY LINE
LINE=1
while read -r CURRENT_LINE
	do
		echo "$LINE: $CURRENT_LINE"
		((LINE++))
done < "./new-filename.txt"


#FUNCTION
function sayhello(){
	echo "Hello World"
}

sayhello


#FUNCTION WITH PARAMETERS
function greet(){
	echo "Hello, I am $1 and I am $2"
}

greet "Brad" "36"



#CREATE FOLDER AND WRITE TO A FILE
mkdir hello
touch "hello/world.txt"
echo "Hello World" >> "hello/world.txt"
echo "Created hello/world.txt"									
