#include <stdio.h>
#include <stdlib.h>




int main(){
   int b=5;
   int *a;
   a=&b;
   void *p;
   p=a;
   
   
   
   
   printf("%d  %p\n",*p,a);
   return 0;
}     
