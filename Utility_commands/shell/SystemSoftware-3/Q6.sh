#install sudo apt-get install pdfposter
#install sudo apt install imagemagick
#change in /etc/ImageMagick-6/policy.xml
# in pdf policy read|write

dirname=/home/manan/Desktop/images
# echo $dirname

if [[ -e $dirname ]]; then
	rm -rf $dirname
fi

mkdir $dirname

for i in *.jpg; do
	f=$(echo $i | sed -E 's/(.*)(.jpg)/\1/g')
	#echo $f.pdf
	convert $i $f.pdf
done

for i in *.jpeg; do
	f=$(echo $i | sed -E 's/(.*)(.jpeg)/\1/g')
	#echo $f.pdf
	convert $i $f.pdf
done

#rm *.jpeg
#rm *.jpg

mv *.pdf $dirname

siz=$(du -h $dirname | awk '{print $1}')
echo "The size of the image folder is $siz"

cd $dirname

for i in *.pdf; do
	f=$(echo $i | sed -E 's/(.*)(.pdf)/\1/g')
	#echo $f.pdf
	convert $i $f.jpg
done

rm *.pdf

for i in *.jpg; do
	f=$(echo $i | sed -E 's/(.*)(.jpg)/\1/g')
	#echo $f.pdf
	convert $i -resize "50%" $f.jpeg
done

for i in *.jpeg; do
	f=$(echo $i | sed -E 's/(.*)(.jpeg)/\1/g')
	#echo $f.pdf
	convert $i $f.pdf
done

rm *.jpeg
rm *.jpg

siz=$(du -h $dirname | awk '{print $1}')
echo "The size of the image folder is $siz"
