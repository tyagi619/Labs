a=$1
b=$2

if [[ ! -r $a ]]; then
	echo "error"
fi

if [[ -f $2 ]]; then
	echo "file exists"
	read ans
fi

if [[ ans=='Y' ]]; then
	cat $a >>$b
fi