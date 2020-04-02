#! /bin/bash

ls -l -1 | awk '{print $9,$8,$6,$7,$1}'

file=$((0))
dir=$((0))

for i in $(ls -1)
do
	if [ -f "$i" ]
	then
		((file++))
	fi
	if [ -d "$i" ]
	then
		((dir++))
	fi
done

echo "Files = $file"
echo "Directories = $dir"				