#! /bin/bash

read -p "Enter two numbers : " a b
gcd(){
	k=$2
	num1=$1
	num2=$2
	while((num2!=0));
		do
			num2=$(($num1%$num2))
			num1=$k
			k=$num2
	done

	echo "$num1"
}

gcd a b
		