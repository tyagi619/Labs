#include <stdio.h>
#include <math.h>


int pallin(char *, int);
int binary(int);


int main(){
  
   int m=0,n=0,M,N,t,s,p,count1=0,count2=0;
   
   scanf("%d %d",&M,&N);
   
    char A[M][N],B[M+N-1];
   for(int i=0;i<M;i++)
      for(int j=0;j<N;j++)
         scanf(" %c",&A[i][j]);
         
   B[0]=A[0][0];
   
   for(int i=0;i<pow(2,M+N-2);i++){
      t=binary(i);
      int count=0;
      for(int j=0;j<M+N-2;j++){
            s=t%10;
            t=t/10;
            if(s)
            count++;
             
      } 
     
      if(count==(M-1)){
         count2++;
         t=binary(i);
         
         m=0;
         n=0;
         for(int j=1;j<=(M+N-2);j++){
            s=t%10;
            t=t/10;
            if(s){
               
               B[j]=A[++m][n];
               
            }   
            else{
               
               B[j]=A[m][++n];
              
            }   
               
         }    
         
         if(pallin(B,M+N-1)){
            for(int j=0;j<=(M+N-2);j++)
               printf("%c",B[j]);
            printf("\n"); 
            count1++;  
         }
      }
   }
   
   printf("%d %d\n",count2,count1);
   return 0;
}


int pallin(char *p,int s){
    int flag=1;
    for(int j=0;j<s/2;j++){
       if(*(p+j)!=*(p+(s-j-1))){
          flag=0;
          return flag;
       }
    }
    return 1;
}


int binary(int s){
   int t=0,j=0;
   while(s!=0){
      t+=(s%2)*pow(10,j);
      s=s/2;
      j++;
   }
   return t;
}                                                
