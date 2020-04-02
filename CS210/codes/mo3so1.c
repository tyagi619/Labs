#include <stdio.h>
#include <stdlib.h>


int main(){
   
   int n;
   scanf("%d",&n);
   int *a;
   a=(int *)malloc(n*sizeof(int));
   
  
   int i,sum=0;
   for(i=0;i<n;i++){
      scanf("%d",&a[i]);
      sum+=a[i];
   }
   int k;
   scanf("%d",&k);
   
   int *b;
   b=(int *)malloc((sum+2)*sizeof(int));  
   
   
   int j=1;
   b[0]=0;
   b[sum+1]=n;
   for(i=0;i<n;i++){
      if(a[i]==1){
         b[j]=i;
         j++;
      }
   }
   
   
   int max=0,t;
   int index;
   for(i=1;i<sum+2-k;i++){
      t=b[i+k]-b[i-1];
      if(i!=1)
         t-=1;
      if(max<t){
         max=t;
         index=i;
      }
   }
      
   for(i=0;i<sum+2;i++)
      printf("%d ",b[i]);
      
   printf("\n");   
   
   for(i=index;i<index+k;i++){
      if(i==index+k-1)
         printf("%d\n",b[i]+1);
      else
         printf("%d,",b[i]+1);
   }
   return 0;
}                  
      
