#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int main(){
   char a[10];
   scanf("%[^\n]",a);
   
   char b[10];
   scanf("%s",b);
  
   int i=0;
   char t1,t2;
   while((a[i]!='\0') || (b[i]!='\0')){
      t1=tolower(a[i]);
      t2=tolower(b[i]);
      
      if(t1==t2){
         i++;
         continue;
      }   
      else{
         printf("%d\n",t1-t2); 
         return 0;
      }
   } 
   
   printf("0\n");
   
   return 0;  
              
}   
   
