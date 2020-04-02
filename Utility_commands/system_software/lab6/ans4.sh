count_words(){
	wc -l $1
}

# echo "enter input size:"
# read n
echo "enter inputs in array form using spaces"

# setopt shwordsplit      # this can be unset by saying: unsetopt shwordsplit
read str
for i in $str;do
	((a[i]++))
done

for i in $str;do
	if [[ ${a[i]} -eq 1 ]]; then
		echo $i
	fi
done
