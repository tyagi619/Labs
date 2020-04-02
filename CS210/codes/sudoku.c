#include <stdio.h>
#define N 9
int count=0;

int Check(int r,int c, int *board,int val);
void solve(int *board,int r,int c);


void main(){
   int board[N][N];
   int i,j;
   for(i=0;i<N;i++)
      for(j=0;j<N;j++)
         scanf("%d",&board[i][j]);
         
   solve(&board[0][0],0,0);
   
   printf("\n\n\n");
   
   for(i=0;i<N;i++){
      for(j=0;j<N;j++){
         printf("%d ",board[i][j]);
      }
      printf("\n");
   }   
         
   
   
}

int Check(int r,int c, int *board,int val){
    int i,j;
    
    for(i=0;i<N;i++)
      if((*(board+r*N+i)==val))
         return 0;
    for(i=0;i<N;i++)
      if((*(board+i*N+c)==val))
         return 0;
    
    int row=(r/3)*3,col=(c/3)*3;
    for(i=0;i<3;i++)
       for(j=0;j<3;j++)
          if(*(board+(row+i)*N+(col+j))==val)
             return 0;     
    
    return 1;
}    


void solve(int *board,int r,int c){
    if(r==N && c==0)
       count++;
       
    
    
    else if(*(board+r*N+c)!=0){
          if(c==N-1)
             solve(board,r+1,0);
          else
             solve(board,r,c+1);
        }       
    
     else{
       int i;
       for(i=1;i<=N;i++){
          if(Check(r,c,board,i)){
              
             *(board+r*N+c)=i;
             if(c==N-1)
                solve(board,r+1,0);
             else
                solve(board,r,c+1);   
          }
          if(count==1)
             break;
          *(board+r*N+c)=0;    
       }
       if(i==N+1){
          printf("NOT SOLVABLE");
          return;
       }   
       
    } 
}       

