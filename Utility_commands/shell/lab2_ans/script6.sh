#! /bin/bash

res=$((0))

while read -n1 i 
do
	if [[ $i =~ [AaEeIiOoUu] ]]
	then
		((res++))
	fi
done < $1

echo "$res"		