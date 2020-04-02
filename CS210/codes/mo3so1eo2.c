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
   
   int j;
   int t,max=0;
   for(i=0;i<n-sum;i++){
      t=0;
      for(j=i;j<i+sum;j++){
         t+=a[j]; 
      }
      if(max<t)
         max=t;
   }
   
   printf("Minimum Number of swaps = %d\n",sum-max);
   
   return 0;
}              
