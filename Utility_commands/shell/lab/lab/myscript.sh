#! /bin/bash

read -p "Enter a string : " STR
LEN=${#STR}
REVERSE=$(echo "$STR" | rev)

if [ $REVERSE == $STR ]
then
	echo "Pallindrome of length $LEN"
else
	echo "Not a Pallindrome"
fi							
