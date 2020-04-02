#include <stdio.h>
#include <stdlib.h>

int main(){
   int n;
   scanf("%d",&n);
   
   int *a;
   a=(int *)malloc(n*sizeof(int));
   
   int i;
   for(i=0;i<n;i++)
      scanf("%d",&a[i]);
      
   int k;
   scanf("%d",&k);
   
   int *b,*c;
   b=(int *)malloc(k*sizeof(int));  
   c=(int *)malloc(k*sizeof(int));
   
   int j;
   int temp;
   for(i=0;i<n-1;i++){
      for(j=i+1;j<n;j++){
         if(a[i]>a[j]){
            temp=a[i];
            a[i]=a[j];
            a[j]=temp;
        }
     }
  }
  
  int min=0,max=0;
  for(i=0;i<k;i++){
     b[i]=a[i];
     c[i]=a[n-i-1];
     min+=b[i];
     max+=c[i];
  }
  
  printf("The two arrays are : ( ");
  
  for(i=0;i<k;i++){
     if(i==k-1)
        printf("%d )  and  ( ",b[i]);
     else
        printf("%d,",b[i]);
  }   
  
  for(i=0;i<k;i++){
     if(i==k-1)
        printf("%d )\n",c[i]);
     else
        printf("%d,",c[i]);
  }   
  
  
  printf("Maximum difference is : %d\n",max-min);
  
  return 0;
}        
              
