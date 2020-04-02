#! /bin/bash

encod()
{
	l=$*
	enc=""
	num=${#l}
	for((i=0;i<$num;i++))
	do
		c=${l:$i:1}
		# echo $c
		if [[ $c =~ [a-z] ]]
		then
			# echo $c
			c=$(printf "%d" \'$c)
			c=$((c+2))
			if ((c>122))
			then
				c=$((c-122+96))	
			fi	
			c=$(echo $c | awk '{printf "%c", $0}')
		elif [[ $c =~ [A-Z] ]]
		then
			# echo $c
			c=$(printf "%d" \'$c)
			c=$((c+2))
			if ((c>91))
			then
				c=$((c-91+64))	
			fi	
			c=$(echo $c | awk '{printf "%c", $0}')
		elif [[ $c =~ [0-9] ]]
		then
			# echo $c
			c=$((c+2))
			if ((c>9))
			then
				c=$((c-9-1))
			fi			
		fi


		enc=${enc}$c
	done			
}



decod()
{
	l=$*
	dec=""
	num=${#l}

	for((i=0;i<$num;i++))
	do

		c=${l:$i:1}
		echo $c
		if [[ $c =~ [a-z] ]]
		then
			c=$(printf "%d" \'$c)
			c=$((c-2))
			if ((c<97))
			then
				c=$((123+c-97))	
			fi	
			c=$(echo $c | awk '{printf "%c", $0}')

		elif [[ $c =~ [A-Z] ]]
		then
			c=$(printf "%d" \'$c)
			c=$((c+2))
			if ((c<65))
			then
				c=$((92-65+c))	
			fi	
			c=$(echo $c | awk '{printf "%c", $0}')

		elif [[ $c =~ [0-9] ]]
		then
			c=$((c-2))
			if ((c<0))
			then
				c=$((10+c))	
			fi	
		fi

		dec=${dec}$c
	done	
}


echo "Enter 1 to encode , 2 to decode , 3 to exit"
read value

if [[ $value -eq 1 || $value -eq 2 ]]
then
	echo "Enter file name"
	read file
	if [[ ! -e $file ]]
	then
		echo "File does not exist"
		exit 0
	else
		if [[ $value -eq 1 ]]
		then	
			while read -r line
			do
				encod $line
				echo $enc >> encoded.txt
			done < ${file}
		else			
			while read -r line
			do
				decod $line
				echo $dec >> decoded.txt
			done < ${file}
		fi
	fi
elif [[ $value -eq 3 ]]
then
	exit 
fi		