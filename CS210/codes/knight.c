#include <stdio.h>
#define N 6
#define M 8



int check(int *board,int r,int c){
    if((r>=0) && (r<N) && (c>=0) && (c<M) && (*(board+r*M+c)==-1))
        return 1;
    else
        return 0;
}            





int solve(int *board,int r, int c,int step){
    if(step==M*N+1)
       return 1;
    
    else{
       int next_r[8]={2,1,-1,-2,-2,-1,2,1};
       int next_c[8]={1,2,2,1,-1,-2,-1,-2};
       int i;
       for(i=0;i<8;i++){
          int row=r+next_r[i];
          int col=c+next_c[i];
          if(check(board,row,col)){
             *(board+row*M+col)=step;
             if(solve(board,row,col,step+1))
                return 1;
             else       
               *(board+row*M+col)=-1;
          }
         
       }
    
    return 0;
   }
}




void main(){
   int board[N][M];
   int i,j;
   for(i=0;i<N;i++)
      for(j=0;j<M;j++)
         board[i][j]=-1;
   
   board[0][0]=1;  

   if(solve(&board[0][0],0,0,2)){
   
      for(i=0;i<N;i++){
         for(j=0;j<M;j++)
            printf("[%2d,%2d, %2d]  ",i,j,board[i][j]);
         printf("\n");
      }      
   }
   else
      printf("Sorry Not Found\n");      
         
}



               
          
    
             
   
