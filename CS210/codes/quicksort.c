#include <stdio.h>
#include <stdlib.h>


int *split(int *begin, int *end){
   int *p=begin;
   int *x;
   int i=0;
   for(x=begin;x<=end-i;x++){
      if(*p<*x && x!=end-i){
         int temp;
            temp=*x;
            *x=*(end-i);
            *(end-i)=temp;
         i++;
         x--;
      }
      else if(x==end-i){
         if(*p>*x){
            int temp;
            temp=*x;
            *x=*p;
            *p=temp;
            return x;
         }
         else if(*p==*x)
            return x;
         else if(*p<*x){
            x--;
            int temp;
            temp=*x;
            *x=*p;
            *p=temp;
            return x;
         }   
      }
   }
} 



int sort(int *begin, int *end){
	if(begin<end){   
	   int *mid;
	   mid=split(begin,end);
	   
	   sort(begin,mid-1);
	   sort(mid+1,end);
	   
	}
	return 0;   
}





int main(){
   int n;
   scanf("%d",&n);
   
   int *a;
   a=(int *)malloc(n*sizeof(int));
   
   int i;
   for(i=0;i<n;i++)
      scanf("%d",&a[i]);
      
   sort(a,(a+(n-1)));
   
   for(i=0;i<n;i++)
      printf("%d ",a[i]);
   printf("\n");
   return 0;
}
           
         
         
         
         
         
                     
