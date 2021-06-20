0#! /bin/bash


#Rename the files accordingly
FILE1=sample.txt
FILE2=days.txt
FILE3=line.txt

#Answer 1
awk 'BEGIN{line=0}{line++}END{print line}' $FILE1

#Answer 2
awk 'BEGIN{count=0}$2==515042969 && a[$3]!=1{a[$3]=1;count++}END{print count}' $FILE1

#Answer 3
awk 'BEGIN{sum=0}{if($2==515042969)sum+=$9+$10}END{print sum}' $FILE1

#Answer 4
#awk 'BEGIN{}$5==1{print $0}END{}' $FILE1

#Answer 5
awk 'BEGIN{count=0}$8>=0.001,$8<=0.009{count++}END{print count}' $FILE1 

#Answer 6
awk 'BEGIN{max=0}length($0)>max{max=length($0)}END{print max}' $FILE1

#Answer 7
#awk 'BEGIN{}NR>=100,NR<=200{print $8,$9,$10}END{}' $FILE1

#Answer 8
awk 'BEGIN{}{if($7<=0){print $0 > "sam1.txt"}else{print $0 > "sam2.txt"}}END{}' $FILE1

#Answer 9
#awk 'BEGIN{x=0;count=1}{if(count%100==1){x++}count++;print $0 > "sample"x".txt"}END{}' $FILE1
#9 files were made


#Answer 10
awk 'BEGIN{}{print NR,$0}END{}' $FILE1

#Answer 11
awk 'BEGIN{}{for(i=1;i<=NF/2;i++){t=$i;$i=$(NF-i+1);$(NF-i+1)=t;} print $0}END{}' $FILE1
#Alternate solution
awk 'BEGIN{}{for(i=NF;i>=1;i--){printf($i)""FS}print "";}END{}' $FILE1

#Answer 12
awk 'BEGIN{max=0}length($0)>max{max=length($0);ans=$2}END{print ans}' $FILE1

#Answer 13
#Same as Answer 12

#Answer 14
awk 'BEGIN{count=0;a["Monday"]=0;a["Tuesday"]=0;a["Wednesday"]=0;a["Thursday"]=0;a["Friday"]=0;a["Saturday"]=0;a["Sunday"]=0;}{for(i=1;i<=NF;i++){a[$i]++;}}END{print a["Monday"],a["Tuesday"],a["Wednesday"],a["Thursday"],a["Friday"],a["Saturday"],a["Sunday"]}' $FILE2


#Answer 15
awk 'BEGIN{}{a[$1]=$0}END{for(i=1;i<=NR;i++)print a[i]}' $FILE3

