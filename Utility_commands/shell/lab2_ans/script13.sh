#!/bin/sh

 touch /home/cse/Downloads/sample.txt
 file=/home/cse/Downloads/sample.txt
 trap "rm -f $file && echo file deleted; exit" 0 2 15

 echo "pid is $$"
 while (( COUNTER < 10 ))
 do
 	sleep 1
 	(( COUNT ++ ))
 		echo $COUNT
 done
 exit 0