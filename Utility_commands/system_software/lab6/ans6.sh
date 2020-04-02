a=$(cat vowels.txt)
for i in $a; do
	for f in $i;do
		if [[ $f =~ [AaEeiIOoUu] ]]; then
			((res++))
		fi
	done
done

echo $res