#! /bin/bash


#sudo apt-get install imagemagick
#You will get a error . copy-paste that error on google and follow the procedure
cd nature_images
mkdir images
LIST=$(ls *.{jpg,jpeg})

for file in $LIST
do
	NAME=$(echo "$file" | sed -E 's/([A-Za-z0-9_-]+)([.]+)([a-z]+)/\1/')
	convert -resize 50% ${file} ${file}
	convert ${file} ./images/${NAME}.pdf
done

rm *.{jpg,jpeg}	 


