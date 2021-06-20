#! /bin/bash

#Q1
# df -h | awk '$NF=="/"{printf "Disk Usage: %s \n" ,$5}'
# free -m | awk 'NR==2{printf "Memory Usage: %.2f%% \n",$3*100/$2}'
# top -bn1 | grep load | awk '{printf "CPU Load: %.2f\n", $(NF-2)}' 
#run using watch -n 5 ./lab.sh


#Q2
# lsusb | awk 'END{if(NR>5){print "USB is Connected"} if(NR<=5){print "USB is not Connected"}}'
#run using watch -n 2 ./lab.sh

#Q3
# cd /home/ravi
# fun(){
# 	FOLDER=$(ls)
# 	echo "$FOLDER"
# 	for folder in $FOLDER
# 	do
# 		if [ -d $folder ]
# 		then
# 			cd $folder
# 			echo "$(pwd)"
# 			fun 
# 			cd ..
# 		fi
# 		rm *.exe *.EXE
# 		rm *.virus
# 	done
# }
# fun

#Q4
# S1=0
# S2=0
# S3=0
# S4=0
# A=2
# B=0
# C=1
# while read -r school num
# 	do
# 		if [ "$school" == "Year$A" ]
# 		then
# 			((B=1))
# 			((A+=2))
# 		elif [ "$school" == "Year$C" ]
# 		then
# 			((B=0))
# 			((C+=2))
# 		elif [ $B == 1 ]
# 		then
# 			if [ $num ]
# 			then
# 				if [ $school == "School1" ]
# 				then
# 					((S1+=$num))
# 				fi
# 				if [ $school == "School2" ]
# 				then
# 					((S2+=$num))
# 				fi
# 				if [ $school == "School3" ]
# 				then
# 					((S3+=$num))
# 				fi
# 				if [ $school == "School4" ]
# 				then
# 					((S4+=$num))
# 				fi
# 			fi
# 		fi
# done < "./school.txt"

# echo "$S1 $S2 $S3 $S4"
# (($S1/10))
# (($S2/10))
# (($S3/10))
# (($S4/10))
# echo "$S1 $S2 $S3 $S4"



#Q5 NOT DONE
# c=0
# while read -r line
# 	do
# 		for s in $(grep -o . <<<"$line")
# 		do
# 			if [ "$s" -ge "0" ] && [ "$s" -le "9" ]
# 			then
# 				((c=9-s))
# 				echo "$c" >> "output.txt"
# 			elif [ "$s" -ge "a" ] && [ "$s" -le "z" ]
# 			then
# 				((c=219-s))
# 				echo "$c">>"output.txt"
# 			elif [ "$s" -ge "A" ] && [ "$s" -le "Z" ]
# 			then
# 				((c=155-s))
# 				echo "$c">>"output.txt"
# 			else
# 				echo "$s">>"output.txt"
# 			fi
# 		done
# done < "./a.txt"

#Q6
#/etc/ImageMagick-6/policy.xml
# cd nature_images
# FILE=$(ls)
# for i in *.jpeg; do
# 	name=$(echo $i | sed -E 's/(.*).jpeg/\1/g')
# 	convert $i $name".pdf"
# done

# for i in *.jpg; do
# 	name=$(echo $i | sed -E 's/(.*).jpg/\1/g')
# 	convert $i $name".pdf"
# done

# rm *.jpg *.jpeg

# mv *.pdf /home/ravi/images

# cd /home/ravi/images

# for i in *.pdf;do
# 	name=$(echo $i | sed -E 's/(.*).pdf/\1/g')
# 	convert $i $name".jpeg"
# 	rm $i
# done
# for i in *.jpeg;do
# 	name=$(echo $i | sed -E 's/(.*).jpeg/\1/g')
# 	convert -resize 50% $i $name"1.jpeg"
# 	rm $i
# done

# for i in *.jpeg;do
# 	name=$(echo $i | sed -E 's/(.*).jpeg/\1/g')
# 	convert $i $name".pdf"
# done




#Q7
# sudo add-apt-repository ppa:malteworld/ppa
# sudo apt update
# sudo apt install pdftk
# count=1
# for((i=1;i<=384;i+=2))
# do
# 	((j=i+1))
# 	pdftk Linux.Shell.Scripting.Cookbook.pdf cat $i $j output newfile"$count".pdf
# 	((count++))
# done