counter=0

echo -e "Time\t Memory \tDisk \t \tCPU"

while [[ $counter -le 60 ]]; do
	
	echo -ne "$counter\t"

	free | awk '(NR>1){total+=$2; used+=$3;} END{ans=used*100/total; printf("%s%%\t",ans)}'

	df | awk '(NR>1){total+=$2; used+=$3;} END{ans=used*100/total; printf("%s%%\t",ans)}'
	top -bn1 | tail -n+8 | awk '{s+=$9} END{printf("%s%%\n",s)}'

	counter=$(($counter+5))
	sleep 5

done
