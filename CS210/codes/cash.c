#include <stdio.h>
#include <stdlib.h>

int max(int *a, int i, int j);

int total(int *a, int i, int j){
   int sum=0,x;
   for(x=i;x<=j;x++)
      sum+=a[x];
   return sum;
}      


int min(int *a,int i, int j){
   if((j-i)==0)
      return a[i];
   else if((j-i)==1)
      return (a[i]>a[j])?a[j]:a[i];
   else{
      return (total(a,i,j)-max(a,i,j));
   }
}      

int max(int *a, int i, int j){
   if((j-i)==0)
      return a[i];
   else if((j-i)==1)
      return (a[i]>a[j])?a[i]:a[j];
   else{
      int leftval=a[i]+min(a,i+1,j);
      int rightval=a[j]+min(a,i,j-1);
      return (leftval>rightval)?leftval:rightval;
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
   
   printf("%d\n",max(a,0,n-1));
   
}   
