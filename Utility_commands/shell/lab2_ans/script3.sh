#! /bin/bash

if [ $(pwd | grep $1) ]
then
	while [ $(pwd | grep $1) ]
	do
		cd ..
	done
	cd $1
else
	echo "Invalid directory"
fi			