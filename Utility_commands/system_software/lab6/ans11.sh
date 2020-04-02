for (( i = 0; i < 1000; i++ )); do
	k=$i
	# echo $k
	((a=k%10))
	((k=k/10))
	((b=k/10))
	((k=k%10))
	c=$k
	# echo $a $b $c
	if ((a*a*a+b*b*b+c*c*c==i)); then
		echo $a $b $c
		echo $i
	fi
done