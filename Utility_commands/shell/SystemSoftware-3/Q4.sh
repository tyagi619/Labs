calc(){ awk "BEGIN { print $*}"; }

iseven=0
eve=0
odd=0

while read -r i ; do
	if [[ $(echo $i | grep "Year") ]]; then
		iseven=$(($iseven+1))
		iseven=$(($iseven%2))
	elif [[ $(echo $i | grep "School") ]]; then
		num=$(echo $i | sed "s/School..//g")
		if [[ iseven -eq 0 ]]; then
			eve=$(($eve+$num))
		else
			odd=$(($odd+$num))
		fi
	fi
done < $1

tot=$(($eve+$odd))

tot=$(calc $tot/4)
eve=$(calc $eve/4)
odd=$(calc $odd/4)

echo "Total avg is $tot"
echo "Even year avg is $eve"
echo "Odd year avg is $odd"