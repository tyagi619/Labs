#include <stdio.h>
#include <stdlib.h>

void sort(int *p,int n);
void func(int *p,int k,int i,int sum);

int main(){
  int n;
  scanf("%d",&n);
  int *p;
  p=(int *)(malloc(n*sizeof(int)));
  int i;
  
  for(i=0;i<n;i++){
     scanf("%d",(p+i));
  }
  
  sort(p,n);
  for(i=0;i<n;i++)
     printf("%d ",p[i]);
  
  printf("\n");   
  
  int sum,index;
  scanf("%d",&sum);
  
  for(i=n-1;i!=-1;i--){
     if(*(p+i)<=sum){
        index=i;
        break;
     } 
  }
  
  for(i=1;i<=index+1;i++){
     func(p,i,index,sum);
  }
  
}          
     
     
void sort(int *p,int n){
    int i,j;
    
    for(i=0;i<n-1;i++){
       for(j=i+1;j<n;j++){
          if(*(p+i)>*(p+j)){
             *(p+i) = *(p+i) + *(p+j);
             *(p+j) = *(p+i) - *(p+j);
             *(p+i) = *(p+i) - *(p+j);
          }
       }
    }
}                   


void func(int *p,int k,int index,int sum){
    int i,j,t=0;
    
    for(i=0;i<index-k;i++){
       for(j=i;j<i+k;j++){
          t+= *(p+j);
       }
       if(t==sum){
         for(j=i;j<i+k;j++)
            printf("%d ", *(p+j));
          printf("\n");   
       }
       t=0;
      }
}    
       
              
    
