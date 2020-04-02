#! /bin/bash

#install pdftk from ubuntu software
#no need to install anything to use convert
mkdir multiple_pdf


for ((i=1;i<=192;i++));
do
	convert Linux.Shell.Scripting.Cookbook.pdf[$((2*i-1))-$((2*i))] ./multiple_pdf/${i}.pdf
	# pdftk Linux.Shell.Scripting.Cookbook.pdf cat $((2*i-1))-$((2*i)) output ./multiple_pdf/${i}.pdf 
done		