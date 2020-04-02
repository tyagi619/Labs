echo "Enter 2 numbers"
read a
read b
res=a
max(){
	if [[ $1 -gt $2 ]]; then
		res=$1
	else 
		res=$2
	fi
}

max $a $b
((b=a+b))
# echo $a $res
((a=res))
# echo $a $res
((b=b-a))
echo $a $res $b
k=$b
while ((b!=0&&a%b!=0)); do
	k=$b
	b=$(($a%$b))
	a=$k
	k=$b
done

echo $k