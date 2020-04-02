#! /bin/bash


#Answer 5
R=$(($RANDOM%19))
R=$(($R+1))
#echo "$R"
for i in 1 2 3
	do
		read -p "Enter a choice : " NUM
		if [ $NUM -eq $R ]
		then
			echo "You guessed it correctly!!"
			exit 2
		elif [ $NUM -lt $R ]
		then
			echo "Entered a number SMALLER"
		else
			echo "Entered a number GREATER"		
		fi
done			
