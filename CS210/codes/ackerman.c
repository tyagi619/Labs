#include <stdio.h>
#include <stdlib.h>

int solve(int x, int y);

void main(){
   int x,y;
   scanf("%d %d",&x,&y);
   int z = solve(x,y);
   printf("%d\n",z);
}


int solve(int x, int y){
   if(x==0){
      printf("%d %d\n",x,y);
      return (y+1);
   }
   else if(y==0){
      printf("%d %d\n",x,y);
      return solve(x-1,1);
   }
   else{
      printf("%d %d\n",x,y);
      return solve(x-1,solve(x,y-1));
   }
}               
