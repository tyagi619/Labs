#include <stdio.h>
#include <stdlib.h>


int main(){
   
   int n;
   scanf("%d",&n);
   
   int *a,*b;
   a=(int *)malloc(n*sizeof(int));
   b=(int *)malloc(n*sizeof(int));
   int i;
   
   for(i=0;i<n;i++){
      scanf("%d",&a[i]);
      b[i]=i;
   }   
      
   int m;
   scanf("%d",&m);
   
   int j;
   int temp;
   for(i=0;i<n-1;i++){
      for(j=i+1;j<n;j++){
         if(a[i]>a[j]){
           temp=a[i];
           a[i]=a[j];
           a[j]=temp;
           temp=b[i];
           b[i]=b[j];
           b[j]=temp;
        }
     }
  }
  
  for(i=0;i<m-1;i++){
     for(j=i+1;j<m;j++){
        if(b[i]>b[j]){
           temp=a[i];
           a[i]=a[j];
           a[j]=temp;
           temp=b[i];
           b[i]=b[j];
           b[j]=temp;
        }
     }
     if(i==m-2)
        printf("%d,%d\n",a[i],a[m-1]);
     else
        printf("%d,",a[i]);   
  }
                  
   
  
   
   return 0;
}                    
            
