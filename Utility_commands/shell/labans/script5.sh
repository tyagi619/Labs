#! /bin/bash


#Answer 5
R=$(($RANDOM%20))
R=$(($R+1))
#echo "$R"
for i in 1 2 3
	do
		read -p "Enter a choice : " NUM
		if [ $NUM -eq $R ]
		then
			echo "You guessed it correctly!!"
			exit
		elif [ $NUM -lt $R ]
		then
			echo "Entered a number SMALLER"
		else
			echo "Entered a number GREATER"		
		fi
done			
