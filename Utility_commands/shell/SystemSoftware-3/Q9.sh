closed=-1
total=0
open=0

while read -r i; do
	
	if [[ $(echo $i | grep "session opened for user sonal") ]]; then
		hour=$(echo $i | sed -E 's/Sep 25 (..):(..):(..) .*/\1/g')
		minute=$(echo $i | sed -E 's/Sep 25 (..):(..):(..) .*/\2/g')
		second=$(echo $i | sed -E 's/Sep 25 (..):(..):(..) .*/\3/g')
		open=$((3600*$hour+60*$minute+$second))
		if [[ $closed -gt -1 ]]; then
			total=$(($total+$open-$closed))
		fi
	elif [[ $(echo $i | grep "session closed for user sonal") ]]; then
		hour=$(echo $i | sed -E 's/Sep 25 (..):(..):(..) .*/\1/g')
		minute=$(echo $i | sed -E 's/Sep 25 (..):(..):(..) .*/\2/g')
		second=$(echo $i | sed -E 's/Sep 25 (..):(..):(..) .*/\3/g')
		closed=$((3600*$hour+60*$minute+$second))
	fi
done < auth.log

hour=$(($total/3600))
total=$(($total-($hour*3600)))

minute=$(($total/60))
total=$(($total-($minute*60)))

echo "$hour:$minute:$total"


