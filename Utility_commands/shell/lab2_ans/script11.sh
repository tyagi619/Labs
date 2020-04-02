#! /bin/bash

for ((i=1;i<1000;i++))
do
	k=$i
	((a=k%10))
	((k=k/10))
	((b=k%10))
	((k=k/10))
	((c=k%10))

	if ((a*a*a+b*b*b+c*c*c==i))
	then
		echo "$i $a $b $c"
	fi
done			