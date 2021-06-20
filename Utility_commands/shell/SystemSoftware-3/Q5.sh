encoder()
{
	init=$*
	num=${#init}
	enc=""
	for (( i = 0; i < $num; i++ )); do
		c=${init:$i:1}
		if [[ $c =~ [a-z] ]]; then
			c=$(printf "%d" \'$c)
			# echo $c
			c=$((97+122-$c))
			# echo $c
			c=$(echo $c | awk '{printf "%c", $0}')
		elif [[  $c =~ [A-Z]  ]]; then
			c=$(printf "%d" \'$c)
			# echo $c
			c=$((65+90-$c))
			# echo $c
			c=$(echo $c | awk '{printf "%c", $0}')
		elif [[ $c =~ [0-9] ]]; then
			c=$((9-$c))
		fi
		enc=${enc}$c
	done
}



while [[ 1 -eq 1 ]]; do
	echo "Enter 1 to encode 2 to decode 3 to exit"
	read option
	if [[ $option -eq 1 || $option -eq 2 ]]; then
		echo "Enter file"
		read file
		if [[ ! -e $file ]]; then
			echo "File does not exist"
			exit 0
		fi

		while read -r i; do
			encoder $i
			echo $enc >> encoder.txt
		done < $file

	elif [[ $option -eq 3 ]]; then
		exit
	else
		echo "Invalid Input"
		exit 1
	fi
done


