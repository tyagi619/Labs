#! /bin/bash


#sudo apt-get install xlsx2csv 
#xlsx2csv marks.xlsx > marks.csv
#xlsx2csv grades.xlsx > grades.csv

#sudo apt-get install unoconv
unoconv -f csv -o marks.csv marks.xlsx
unoconv -f csv -o grades.csv grades.xlsx

awk 'BEGIN{OFS=FS=","} FNR==NR,NF>0{a[$2]=$3 ; next;} {print $1,$2,$3,$7,a[$2] > "marks.csv"} END{}' grades.csv marks.csv

unoconv -f xlsx -o final_marks.xlsx marks.csv