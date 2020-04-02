#include <stdio.h>
#include <stdlib.h>


int main(){
   
   int n1;
   scanf("%d",&n1);
   
   int *a;
   a=(int *)malloc(n1*sizeof(int));
   
   int i;
   
   for(i=0;i<n1;i++)
      scanf("%d",(a+i));
   
   int n2;
   scanf("%d",&n2);
   
   int *b;
   b=(int *)malloc(n2*sizeof(int));
   
   for(i=0;i<n2;i++)
      scanf("%d",(b+i));
      
   int min = *a;
   
   for(i=1;i<n1;i++)
      if(min>*(a+i))
         min=a[i];
         
   int count=0;
   for(i=0;i<n2;i++)
      if(b[i]<=min)
         count++;
   
   printf("%d\n",count);
   
   return 0;
}   
                    
