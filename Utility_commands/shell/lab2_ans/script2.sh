#! /bin/bash

echo "" > "./shell_question/output/1.ouput"
echo "" > "./shell_question/output/2.ouput"


num_load(){
	# awk 'BEGIN{FS="|"} {for(i=1;i<=NF;i++){if($i=="num loads from remote cache"){print NR,$i > "$2"}}}' "$1"
	grep "num loads from remote cache" $1 >> $2 
}

value_sum(){
	awk 'BEGIN{FS="|";sum=0}{for(i=1;i<=NF;i++){if($i ~ /[\t ]*[0-9]*/){sum+=$i}}}END{print sum}' $1 > $2
}

num_load "./shell_question/1/1.out" "./shell_question/output/1.ouput"
num_load "./shell_question/2/2.out" "./shell_question/output/1.ouput"
num_load "./shell_question/3/3.out" "./shell_question/output/1.ouput"

value_sum "./shell_question/output/1.ouput" "./shell_question/output/2.ouput"