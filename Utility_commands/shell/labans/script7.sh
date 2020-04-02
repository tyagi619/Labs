#! /bin/bash

#Answer 6
read -p "Enter a string" STR
LEN=${#STR}

#rev is used to reverse lines 

#reverse=$(echo "$name" | rev)

if [[ $(rev <<< "$STR") == "$STR" ]]
then
	echo "Pallindrome of $LEN"
else
	echo "Not Pallindrome"
fi	


#Answer 7 a)
cd $1
LIST=$(ls)

for FILE in $LIST
	do
		if [ $FILE == $2 ]
		then
			echo "$FILE is a file"
		fi
done

#Answer 7 b)
cd $1
LIST=$(ls)
COUNT=0

for FILE in $LIST
	do
		((COUNT++))
done		

echo "$COUNT"	

#Answer 7 c)
cd $1
for F in 'ls -1 *.c'
	do
		rm $F
done		
#Answer 7 d)
cd $1
for F1 in 'ls -1'
	do
		if [ ! -s $F1 ]
		then
			rm $F1
		fi
done			


#Answer 8
cp ./$1 ./backup-$1

#Answer 9 a)
awk '{print "" > $1".txt"}' $1

#ANswer 9 b)
awk '{if($1>=17491011 && $1<=17491015 && $1%2==1 && $2=="CS241")print "Roll No.:",$1,"Subject:",$2}' $1
		
