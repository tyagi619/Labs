dir=$1 #storing the name of the directory
k=$(pwd | grep -e "$dir")
echo $k
while [[ ! -z $k ]] && [[ $k != "/" ]]; do
	cd ..
	k=$(pwd | grep -e "$dir$")
	# echo $k
done
pwd
if [[ $k == "/" ]]; then
	echo "dir not present"
else
	cd $dir
fi


