#include <stdio.h>
#include <stdlib.h>


void mergesort(int *a,int l,int m, int r){
   int n1=m-l+1;
   int n2=r-m;
   
   int L[n1];
   int R[n2];
   int i;
   for(i=0;i<n1;i++)
      L[i]=a[l+i];
   for(i=0;i<n2;i++)
      R[i]=a[m+1+i];
      
   int k=l;
   i=0;
   int j=0;
   
   while(i!=n1 && j!=n2){
      if(L[i]<R[j]){
         a[k]=L[i];
         i++;
      }
      else{
         a[k]=R[j];
         j++;
      }
      k++;
   }
   
   
   for(j=j;j<n2;j++){
      a[k]=R[j];
      k++;
     
   }  
   
   for(i=i;i<n1;i++){
      a[k]=L[i];
      k++;
     
   }
   
}                      


void merge(int *a,int l, int r){
   if(l<r){
      int m=l+(r-l)/2;
      
      merge(a,l,m);
      merge(a,m+1,r);
      
      mergesort(a,l,m,r);
   }
   
}      

int main(){
   int n;
   scanf("%d",&n);
   
   int *a;
   a=(int *)malloc(n*sizeof(int));
   int i;
   for(i=0;i<n;i++)
      scanf("%d",&a[i]);   
      
   merge(a,0,n-1);
   
   for(i=0;i<n;i++)
      printf("%d ",a[i]);
      
   printf("\n");
   
   return 0;
}         
