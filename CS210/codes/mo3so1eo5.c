#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


int main(){
   char s[10];
   
   scanf("%[^\n]",s);
   
   int i;
   int t;
   int z=0;;
   int x;
   
   for(i=0;s[i]!='\0';i++){
      t=s[i];
      z+=t;
   }
   
   
   x = sqrt(z);
   
   if(x*x == z)
      printf("1\n");
   else
      printf("0\n");
      
   return 0;
}            
      
