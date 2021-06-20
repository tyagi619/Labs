num_load(){
	awk '/num loads from remote cache/{print $0}' ./2/2.out ./1/1.out ./3/3.out >./output/1.out
	# pwd
}

value_sum(){
	awk 'BEGIN {sum=0} {for(i=7;i<=NF;i=i+2)	{sum=sum+$i;print $i};print sum} END {print sum}' ./output/1.out 
	# echo 4
}


# value_sum
value_sum