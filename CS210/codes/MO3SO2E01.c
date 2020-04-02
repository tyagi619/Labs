#include <stdio.h>

int total(int *p,int n1,int n2,int n3,int col,int row);

void main(){
   int n,m,i,j,ques,s,h,x;
   scanf("%d %d",&n,&m);
   int loc[n][m];
   
   for(i=0;i<n;i++){
     for(j=0;j<m;j++)
        scanf("%d",&loc[i][j]);
   }     
   
   scanf("%d",&ques);
   int result[ques];
   
   for(i=0;i<ques;i++){
      
      scanf("%d %d %d",&x,&s,&h);
      
      result[i]=total(&loc[0][0],x,s,h,m,n);
      
   }
   
   for(i=0;i<ques;i++)
      printf("%d\n",result[i]);
}

int total(int *p,int n1,int n2,int n3,int col,int row){
       int sum=0,k=1;
        
        
        while(k<(2*n1)){
           
            if((n2-n1+k)>=0 && (n2-n1+k)<row && (n3-n1)>=0)
                sum+=*(p+(n2-n1+k)*col+(n3-n1));
            
            if((n2-n1+k)>=0 && (n2-n1+k)<row && (n3+n1)<col)
                sum+=*(p+(n2-n1+k)*col+(n3+n1));
            
            if((n3-n1+k)>=0 && (n3-n1+k)<col && (n2-n1)>=0)
                sum+=*(p+(n2-n1)*col+(n3-n1+k));
            
            if((n3-n1+k)>=0 && (n3-n1+k)<col && (n2+n1)<row)
                sum+=*(p+(n2+n1)*col+(n3-n1+k));
             
            k++;                
        }
        
        if((n2-n1)>=0 && (n3-n1)>=0)
              sum+=*(p+(n2-n1)*col+(n3-n1));
        
        if((n2-n1)>=0 && (n3+n1)<col)
              sum+=*(p+(n2-n1)*col+(n3+n1));        
        
        if((n2+n1)<row && (n3-n1)>=0)
              sum+=*(p+(n2+n1)*col+(n3-n1));        
        
        if((n2+n1)<row && (n3+n1)<col)
              sum+=*(p+(n2+n1)*col+(n3+n1)); 
              
        return sum;
 }                                                
