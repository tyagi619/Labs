#include <stdio.h>
#include <assert.h>
#define N 8
int count=0;

int Check(int r,int c, int *board);
void solve(int *board,int r,int n);


void main(){
   int n;
   scanf("%d",&n);
   assert(n>=1 && n<=92);
   int board[N][N]={{0}};
   solve(&board[0][0],0,n);
   
   
   int i,j;
   for(i=0;i<N;i++){
      for(j=0;j<N;j++){
         if(board[i][j]==1)
            printf(" Q ");
         else
            printf(" _ ");
      }
      printf("\n");
   }         
               
   
   
}

int Check(int r,int c, int *board){
    int i;
    
    for(i=0;i<N;i++)
      if(*(board+r*N+i)==1&&i!=c)
         return 0;
    for(i=0;i<N;i++)
      if(*(board+i*N+c)==1&&i!=r)
         return 0;
    
    for(i=-N;i<N;i++)
    {
    	if(i!=0)
    	{
    		int row = r+i;
    		int column = c+i;
    		if(row>=0&&row<N&&column>=0&&column<N)
    		{
    			if(*(board+row*N+column)==1)
    				return 0;
    		}
    		row = r-i;
    		column = c+i;
    		if(row>=0&&row<N&&column>=0&&column<N)
    		{
    			if(*(board+row*N+column)==1)
    				return 0;
    		}
    	}
    }
    return 1;
}    


void solve(int *board,int r,int n){
    if(r==N)
       count++;
    
    else{
       int i;
    
       for(i=0;i<N;i++){
          if(Check(r,i,board)){
             *(board+r*N+i)=1;
             solve(board,r+1,n);
             if(count==n)
                break;
             *(board+r*N+i)=0;
          }
          
       }
    }
}             
            
             
