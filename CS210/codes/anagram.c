#include <stdio.h>


void main(){
   int n,flag;
   scanf("%d",&n);
   
   char s[n][30];
   int i,j;
   for(i=0;i<n;i++)
      scanf("%s", s[i]);
      
   int alphabet[n][26];
   
   for(i=0;i<n;i++)
      for(j=0;j<26;j++)
         alphabet[i][j]=0;
   int l;
   for(i=0;i<n;i++){
      for(l=0;s[i][l]!='\0';l++);
      for(j=0;j<l;j++){
         if(s[i][j]>=97 && s[i][j]<=122)
             alphabet[i][s[i][j]-97]++;
      }
   }
   
   int count=0,k,x=0;
   int arr[n];
   for(i=0;i<n;i++)
      arr[i]=-1;
   
   for(i=0;i<n-1;i++){
      for(j=i+1;j<n;j++){
         flag=0;
         for(k=0;k<26;k++){
            flag=0;
            if(alphabet[i][k]!=alphabet[j][k]){
               flag=1;
               break;
            }
         }
         if(flag==0){
            count++;
            if(count==1){
               count++;
               arr[x]=i;
               x++;
               arr[x]=j;
               x++;
            }
            else{
              arr[x]=j;
              x++;
            }     
            i=j-1;
            j=n;
            
         }
      }
   } 
   
   printf("%d\n",count);
   /*for(i=0;i<n;i++)
      printf("%d ",arr[i]);
   printf("\n");*/    
   
   for(i=0;i<n;i++){
      if(arr[i]!=-1){
         for(j=0;s[arr[i]][j]!='\0';j++){
            printf("%c",s[arr[i]][j]);
         }
         printf("\n");
      }
   } 
}   
                                
