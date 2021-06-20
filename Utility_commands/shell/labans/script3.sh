#! /bin/bash

#Answer 3 a)
read -p "Enter four numbers : " NUM1 NUM2 NUM3 NUM4
ANS=$(($NUM1+$NUM2+$NUM3+$NUM4))
echo "Sum of four numbers is $ANS"
#alternative ans
echo "Sum of four numbers is $(($NUM1+$NUM2+$NUM3+$NUM4))"


#Answer 3 b)
# "$#" counts the number of command line arguments
#Command line arguments are given as ./script3.sh arg1 arg2
if [ $# -eq 0 ]
then
	echo "both command arguments missing"
	#exit 2
elif [ $# -eq 1 ]
then
	echo "one command line argument missing"
	#exit 2
else
	echo "Sum is : $(($1+$2))"	
fi	

#Answer 3 c)
SUM=0
for NUM in $@
	do
		if [ $NUM -ge 10 ] && [ $NUM -le 20 ]
		then	
			SUM=$(($NUM+$SUM))
		fi		
done

echo "Sum is : $SUM"			


			
