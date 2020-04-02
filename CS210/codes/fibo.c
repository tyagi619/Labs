#include <stdio.h>
#include <stdlib.h>

int fab(int *a, int k);

int main(){
   int k;
   scanf("%d",&k);
   
   int *a;
   a=(int *)malloc((k+1)*sizeof(int));
   
   a[0]=-1;
   a[1]=0;
   a[2]=1;
   
   int i;
   
   for(i=3;i<k+1;i++)
      a[i]=-1;
      
   printf("%d\n",fab(&a[0],k));  
   for(i=1;i<k;i++)
      printf("%d ",a[i]);
   printf("\n");    
      
   return 0;
}


int fab(int *a, int k){
      int t1=((k/2)+1);
      int t2=(k/2);
      
      if(a[t2]==-1)
         *(a+t2)=fab(&a[0],t2);
      if(a[t1]==-1)
         *(a+t1)=fab(&a[0],t1);
   if(k%2==0){
     
      return (((a[t1])*(a[t1]))+((a[t2])*(a[t2])));      
         
   }      
   else{
      return ((2*(a[t2])*(a[t1]))+((a[t1])*(a[t1])));
   
   }
}   
   
