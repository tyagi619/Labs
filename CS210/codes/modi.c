#include <stdio.h>
#include <stdlib.h>
int amtadd(int *,int,int,int,int,int);
int main()
{
    int M,N,c,i,j,sum;
    scanf("%d %d",&M,&N);
    int A[M+4][N+4];
    for(i=0;i<(M+4);i++)
        for(j=0;j<(N+4);j++)
        A[i][j]=0;
    for(i=2;i<(M+2);i++)
        for(j=2;j<(N+2);j++)
            scanf("%d",&A[i][j]);
    for(i=0;i<(M+4);i++){
        for(j=0;j<(N+4);j++)
        	printf("%d",A[i][j]);
        	printf("\n");
    }
    scanf("%d%d%d",&c,&i,&j);
    sum=amtadd(&A[0][0],c,M+4,N+4,i,j);
    printf("%d",sum);
    return 0;
}
int amtadd(int *p,int x,int r,int c,int y,int z){
int sum=0;
if(x==0)
    sum=*(p+(y+2)*c+z+2-1)+*(p+(y+2)*c+z+2+1)+*(p+(y+2-1)*c+z+2)+*(p+(y+2+1)*c+z+2);
else
    sum=*(p+(y+2-2)*c+z+2-1)+*(p+(y+2-2)*c+z+2+1)+*(p+(y+2-1)*c+z+2-2)+*(p+(y+2-1)*c+z+2+2)+*(p+(y+2+1)*c+z+2-2)+*(p+(y+2+1)*c+z+2+2)+*(p+(y+2+2)*c+z+2-2)+*(p+(y+2+2)*c+z+2+2);
return sum;
}


