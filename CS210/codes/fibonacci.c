#include<stdio.h>
int fibo(int);
int main(){
int k;
scanf("%d",&k);
printf("%d\n",fibo(k));
return 0;
}
int fibo(int k){
if(k==2)
return 1;
else if(k==1)
return 0;
else if(k%2==0)
return fibo(k/2+1)*fibo(k/2+1)+fibo(k/2)*fibo(k/2);
else
return 2*fibo(k/2)*fibo(k/2+1)+fibo(k/2+1)*fibo(k/2+1);
}
