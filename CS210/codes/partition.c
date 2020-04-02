#include <stdio.h>
#include <stdlib.h>

void sort1(int *A,int start,int end,int min,int max,int a,int n){
	if(a==n)
	   return;
	else if(*(A+a)<min){
	printf("%d ",*(A+a));
	a++;
	sort1(A,start,end,min,max,a,n);
	}
	else{
	a++;
	sort1(A,start,end,min,max,a,n);
	}
}
void sort2(int *A,int start,int end,int min,int max,int a,int n){
	if(a==n)
	   return;
	else if((*(A+a)>min)&&(*(A+a)<max)){
	printf("%d ",*(A+a));
	a++;
	sort2(A,start,end,min,max,a,n);
	}
	else{
	a++;
	sort2(A,start,end,min,max,a,n);
	}
}
void sort3(int *A,int start,int end,int min,int max,int a,int n){
	if(a==n)
	   return;
	else if(*(A+a)>max){
	printf("%d ",*(A+a));
	a++;
	sort3(A,start,end,min,max,a,n);
	}
	else{
	a++;
	sort3(A,start,end,min,max,a,n);
	}
}
int main(){
	int min,max,n;
	scanf("%d",&n);
	int *A;
	A=(int *)malloc(n*sizeof(int));
	int i;
	for(i=0;i<n;i++)
	scanf("%d",&A[i]);
	scanf("%d %d",&min,&max);
    sort1(A,0,n-1,min,max,0,n);
    printf("%d ",min);
    sort2(A,0,n-1,min,max,0,n);
    printf("%d ",max);
    sort3(A,0,n-1,min,max,0,n);
	 
	return 0;
}

