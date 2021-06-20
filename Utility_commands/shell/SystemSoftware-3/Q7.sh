#install sudo apt install imagemagick
#change in /etc/ImageMagick-6/policy.xml
# in pdf policy read|write

dirname=/home/manan/Desktop/Success
# echo $dirname

if [[ -e $dirname ]]; then
	rm -rf $dirname
fi

mkdir $dirname

temp=./multiple_pdf
# echo $dirname

if [[ -e $temp ]]; then
	rm -rf $temp
fi

mkdir $temp

counter=1
for (( i = 0; i < 384; i=i+2 )); do
	next=$(($i+1))
	convert Linux.Shell.Scripting.Cookbook.pdf[$i-$next] file$counter.pdf
	counter=$(($counter+1))
done

mv file*.pdf $temp

cd $temp

mv file*.pdf $dirname

cd ..
rm -rf $temp
