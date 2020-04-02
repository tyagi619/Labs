#! /bin/bash

#Answer 4
read -p "Enter two numbers : " NUM1 NUM2
read -p "WHAT DO YOU WANT TO PERFORM : " OPERATION
case "$OPERATION" in
	[Aa][dD][dD])
		echo "Sum is : $(($NUM1+$NUM2))"
		;;
	[Ss][Uu][Bb][Tt][rR][aA][cC][Tt])
		echo "Subtarction is : $(($NUM1-$NUM2))"
		;;
	[Mm][Uu][Ll][Tt][Ii][Pp][Ll][Yy])
		echo "Multiply is : $(($NUM1*$NUM2))"
		;;
	[Dd][Ii][Vv][Ii][Dd][Ee])
		echo "Divide is : $(($NUM1/$NUM2))"
		;;
	*)
		echo "No match found"
		;;
esac				

#if user gave the input as operator
read -p "Enter two numbers : " NUM1 NUM2
read -p "WHAT DO YOU WANT TO PERFORM : " OPERATOR
echo "Ans is : $((${NUM1}${OPERATOR}${NUM2}))"
case "$OPERATOR" in
	"+")
		echo "Sum is : $(($NUM1+$NUM2))"
		;;
	"-")	
		echo "Difference is : $(($NUM1-$NUM2))"
		;;
	"*")	
		echo "Product is : $(($NUM1+$NUM2))"
		;;
	"/")
		echo "Divide is : $(($NUM1/$NUM2))"
		;;
	*)
		echo "No input"
		;;
esac				
