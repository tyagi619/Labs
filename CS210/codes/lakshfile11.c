#include<stdio.h>

int main(int argc,char *argv[]){

long pos1,pos2,pos3,pos4;
FILE *a,*b,*c;
int d,e;
a=fopen(argv[1],"r");
b=fopen(argv[2],"r");
c=fopen(argv[3],"w+");

fseek(a,0L,SEEK_END);
fseek(b,0L,SEEK_END);
pos1=ftell(a);
pos2=ftell(b);
rewind(a);
pos3=ftell(a);
pos4=ftell(c);
if(pos1>=pos2){
while(pos2>0){

if(pos4%2==1){
d=fgetc(a);
fputc(d,c);
}
else{
fseek(b,-1L,SEEK_CUR);
e=fgetc(b);
fputc(e,c);
fseek(b,-1L,SEEK_CUR);
}
pos4=ftell(c);
pos2=ftell(b);
}
while((d=fgetc(a))!=EOF){
fputc(d,c);
}
}

else{
while(pos3<=pos1){

if(pos3%2==0){
d=fgetc(a);
fputc(d,c);
}
else{
fseek(b,-1L,SEEK_CUR);
e=fgetc(b);
fputc(e,c);
fseek(b,-1L,SEEK_CUR);
}
pos3=ftell(a);
}
while(pos2>0){
fseek(b,-1L,SEEK_CUR);
e=fgetc(b);
fputc(e,c);
fseek(b,-1L,SEEK_CUR);
pos2=ftell(b);
}
}
fclose(a);
fclose(b);
fclose(c);
return 0;
}





