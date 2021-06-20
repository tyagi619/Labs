#install csvtool and gnumeric
ssconvert marks.xlsx marks.csv
ssconvert grades.xlsx grades.csv

csvtool pastecol 8 3 marks.csv grades.csv > temp.csv

cp temp.csv marks.csv

rm grades.csv temp.csv

awk 'BEGIN{FS=","; OFS=","} {print $1,$2,$3,$7,$8}' marks.csv > temp.csv

cp temp.csv marks.csv

rm temp.csv

ssconvert marks.csv final_marksheet.xlsx
