#! /bin/bash

if [ -r "$1" ]
then
	cat "$1" >> "$2"
else
	echo "$1 is not readable"
fi		