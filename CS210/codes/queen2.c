#include <stdio.h>
#define N 8
int count=0;

int Check(int r,int c, int *board);
void solve(int *board,int r);
 

void main(){
   int board[N][N]={{0}};
   solve(&board[0][0],0);
   
   printf("%d\n",count);
   
   
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


void solve(int *board,int r)
{
    if(r==N)
       count++;
    
    else
    {
       int i;
    
       for(i=0;i<N;i++)
       {
          if(Check(r,i,board))
          {
             *(board+r*N+i)=1;
             solve(board,r+1);
             *(board+r*N+i)=0;
          }
        
       }
    }
}             
            
             
