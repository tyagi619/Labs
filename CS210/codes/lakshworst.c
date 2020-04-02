#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int count=0;

int digit[200];
int inuse[11];
int assign(char sum[],char w[],char x[],char y[],char z[],int idx,int carry);
void getletter(char *from,char *to){
int i,l;
for(l=0;from[l]!='\0';l++);
for(i=0;i<l;i++)
to[i]=from[l-1-i];
}

void printonenum(char n[]){
int i;
for(i=10;i>=0;i--){
if(n[i]==' '||n[i]=='0'||digit[n[i]]>9||digit[n[i]]<0)
printf(" %c",n[i]);
else
printf(" %d",digit[n[i]]);}
printf("\n");
}

void printpuzzle(char sum[],char w[],char x[],char y[],char z[]){
int i;
printonenum(w);
printonenum(x);
printonenum(y);
printonenum(z);
printf(" ");
for(i=10;i>=0;i--){
if(sum[i]==' ') printf("  ");
else printf("- ");
}
printf("\n");
printonenum(sum);
printf("\n");
}

int gencarry(char sum[],char w[],char x[],char y[],char z[],int idx,int carry){
if(sum[idx]!=' '){
	if((digit[x[idx]]+digit[y[idx]]+digit[z[idx]]+digit[w[idx]]+carry)%10==digit[sum[idx]]){
		int t=digit[w[idx]]+digit[x[idx]]+digit[y[idx]]+digit[z[idx]]+carry;
		carry=t/10;
		idx++;
		if(idx==11&&carry==0)
		{
		count++;
		return 1;
		}
		else
		return assign(sum,w,x,y,z,idx,carry);
		}
		else 
		return 0;
	}
else if(sum[idx]==' '&&carry==0)
{
count++;
return 1;
}
else 
return 0;
}

int assignz(char sum[],char w[],char x[],char y[],char z[],int idx,int carry){
if(digit[z[idx]]==z[idx]){
	int i;
	for(i=0;i<10;i++){
		if(inuse[i]==0){
			digit[z[idx]]=i;
			inuse[i]=1;
			if(gencarry(sum,w,x,y,z,idx,carry))
			return 1;
			else{
			digit[z[idx]]=z[idx];
			inuse[i]=0;
			}
		}
		}
	return 0;
	}
else 
return gencarry(sum,w,x,y,z,idx,carry);
}

int assigny(char sum[],char w[],char x[],char y[],char z[],int idx,int carry){
if(digit[y[idx]]==y[idx]){
	int i;
	for(i=0;i<10;i++){
		if(inuse[i]==0){
			digit[y[idx]]=i;
			inuse[i]=1;
			if(assignz(sum,w,x,y,z,idx,carry))
			return 1;
			else{
			digit[y[idx]]=y[idx];
			inuse[i]=0;
			}
		}
		}
	return 0;
	}
else 
return assignz(sum,w,x,y,z,idx,carry);
}

int assignx(char sum[],char w[],char x[],char y[],char z[],int idx,int carry){
if(digit[x[idx]]==x[idx]){
	int i;
	for(i=0;i<10;i++){
		if(inuse[i]==0){
			digit[x[idx]]=i;
			inuse[i]=1;
			if(assigny(sum,w,x,y,z,idx,carry))
			return 1;
			else{
			digit[x[idx]]=x[idx];
			inuse[i]=0;
			}
		}
		}
	return 0;
	}
else 
return assigny(sum,w,x,y,z,idx,carry);
}

int assignw(char sum[],char w[],char x[],char y[],char z[],int idx,int carry){
if(digit[w[idx]]==w[idx]){
	int i;
	for(i=0;i<10;i++){
		if(inuse[i]==0){
			digit[w[idx]]=i;
			inuse[i]=1;
			if(assignx(sum,w,x,y,z,idx,carry))
			return 1;
			else{
			digit[w[idx]]=w[idx];
			inuse[i]=0;
			}
		}
		}
	return 0;
	}
else 
return assignx(sum,w,x,y,z,idx,carry);
}

int assign(char sum[],char w[],char x[],char y[],char z[],int idx,int carry){
if(digit[sum[idx]]==sum[idx]){
	int i;
	for(i=0;i<10;i++){
		if(inuse[i]==0){
			digit[sum[idx]]=i;
			inuse[i]=1;
			if(assignw(sum,w,x,y,z,idx,carry))
			{
				if(count<=5)
				{
				printpuzzle(sum,w,x,y,z);
				digit[sum[idx]]=sum[idx];
				inuse[i]=0;
				}
				else return 1;
			}
			else{
			digit[sum[idx]]=sum[idx];
			inuse[i]=0;
			}
		}
	}
	return 0;
	}
else 
return assignw(sum,w,x,y,z,idx,carry);
}

int main(){
char a[]="",b[]="OHIO",c[]="KANSAS",d[]="MAINE",e[]="STATES";
char array[4][11],sum[11];
int i;
for(i=0;i<200;i++) digit[i]=i;
digit[' ']=0;
digit['0']=0;
for(i=0;i<11;i++){
array[0][i]=' ';
array[1][i]=' ';
array[2][i]=' ';
array[3][i]=' ';
sum[i]=' ';
inuse[i]=0;
}
getletter(a,&array[0][0]);
getletter(b,&array[1][0]);
getletter(c,&array[2][0]);
getletter(d,&array[3][0]);
getletter(e,sum);
printpuzzle(sum,&array[0][0],&array[1][0],&array[2][0],&array[3][0]);
assign(sum,&array[0][0],&array[1][0],&array[2][0],&array[3][0],0,0);
if(count){
printf("no of solution exist: %d\n",count);
printf("\n");
//printpuzzle(sum,&array[0][0],&array[1][0],&array[2][0],&array[3][0]);
}
else
printf("solution doesn't exist");
return 0;
}










