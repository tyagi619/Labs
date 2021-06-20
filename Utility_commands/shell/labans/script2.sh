#! /bin/bash


#Answer 2 a)
CURRENT_DIRECTORY=$(pwd)
echo "$CURRENT_DIRECTORY"
#Alternate
pwd

#Answer 2 b)
#Note USER is a built in variable for current username
echo "$USER"


#Answer 2 c)
TODAY=$(date +%d/%m/%Y)
echo "Today is : $TODAY"
