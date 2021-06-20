#! /bin/bash

tot=0
bool=0

while read -r line
do
	if [[ $(echo $line|grep "Year") ]]
	then
		c=$(echo $line|sed -E 's/(Year)([0-9]+)/\2/')
		if [[ $c -eq 8 || $c -eq 9 || $c -eq 10 ]]
		then
			bool=$((bool+1))
			bool=$((bool%2))
		fi
	elif [[ $(echo $line|grep "School") ]]
	then
		if [[ $bool -eq 1 ]]
		then	
			c=$(echo $line|sed -E 's/(School)([0-9]+) ([0-9]+)/\3/')
			tot=$((tot+c))
		fi
	fi
done < "school_database.txt"

echo $tot			


