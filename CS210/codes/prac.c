#include <stdio.h>
#include <stdlib.h>



int main(int argc,char *argv[]){

   FILE *fp1;
   FILE *fp2;
   FILE *fp3;
   
   fp1=fopen(argv[1],"r");
   fp2=fopen(argv[2],"r");
   fp3=fopen(argv[3],"w");
   
   int c1=0;
   int c2;
   //int flag=0;
   
   fseek(fp2,-1L,SEEK_END);
   int pos=ftell(fp2);
   
   while((c1!=EOF) || pos>0){
      
      c1=fgetc(fp1);
      if(c1!=EOF)
      {
         fputc(c1,fp3);   
      }
      
      if(pos>0)
      {
         fseek(fp2,-1L,SEEK_CUR);
         c2=fgetc(fp2);
         fputc(c2,fp3);
         fseek(fp2,-1L,SEEK_CUR);
         pos=ftell(fp2);
      }
   }
   
   fclose(fp1);
   fclose(fp2);
   fclose(fp3);
   
   return 0;
}           
         
      
   
   
   
