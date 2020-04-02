#! /bin/bash

if [[ -r "$1" && -f "$1" ]]
then
	if [ -f "$2" ]
	then
		cat "$1" >> "$2"
	else
		echo "$2 does not exist"
	fi		
else
	echo "$1 is not readable"
fi		