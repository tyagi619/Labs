#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main(){
   char s[100];
   scanf("%[^\n]",s);
   
   int i=0;
   int a=0,t=0,g=0,c=0;
   int index;
   int j;
   
   while(s[i]!='\0'){
      
      if(a==0 && t==0 && g==0 && c==0)
         index=i;
      if(s[i]=='A')
         a++;
      if(s[i]=='T')
         t++;   
      if(s[i]=='G')
         g++;
      if(s[i]=='C')
         c++; 
      if(a>1 || t>1 || c>1 || g>1 || s[i+1]=='\0'){
         if(s[i+1]=='\0'
         if(index!=i-1){
            printf("Start Index : %d      End Index : %d\n",index,i-1);
            for(j=index;j<i;j++)
               printf("%c ",s[j]);
            printf("\n");  
            i=i-2;
         }
         //else if(index==i-1)
            //i--;
         
         a=0;
         t=0;
         g=0;
         c=0;
      }
      i++;
   }
   return 0;
}             
                       
