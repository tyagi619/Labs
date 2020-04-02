#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int count=0;
int digit[200], /* Digit value for char with code of index */
inuse[11]; /*Digits already in use. Actually only 10 needed*/
int assign(char sum[], char x[], char y[], char z[],int idx, int carry);

char * getLetters(char *from, char *to)
{
/* ******************************************************
* Recursive function to move chars in string from
* into array to. Reverses order to help align letters
* in puzzle words on unit position (index 0 in to)
* *****************************************************/
   int l;
   for(l=0;from[l]!='\0';l++);
   int i;
   for(i=0;i<l;i++)
      to[i]=from[l-i-1];
}


void printOneNum(char n[])
{
/* Code provided for training purposes */
int i;
for (i = 10; i>=0; i--)
if (n[i] == ' ' || digit[n[i]] > 9 ||
digit[n[i]] <0 || n[i] =='0')
printf(" %c", n[i]);
else printf("%2d", digit[n[i]]);
printf("\n");
}


void printPuzzle(char sum[], char x[], char y[], char z[])
{
int i;
printOneNum(x);
printOneNum(y);
printOneNum(z);
//printf(" ");
for (i = 10; i>=0; i--)
if (sum[i] == ' ')
printf("  ");
else printf("--");
printf("\n");
printOneNum(sum);
printf("\n");
}


int genCarry (char sum[], char x[], char y[], char z[],int idx, int carry)
{
/* ************************************************
* Checks that values for letters at inddex idx
* in arrays x, y and z add to letter value in sum.
* Carry is carry in. Computes carry out (carry
* into idx+1) that is returned as function value.
* Carry out of -1 denotes letter values are wrong.
* ***********************************************/
	if(sum[idx]!=' '){
		if((digit[x[idx]]+digit[y[idx]]+digit[z[idx]]+carry)%10 == digit[sum[idx]]){
		   int t=(digit[x[idx]]+digit[y[idx]]+digit[z[idx]]+carry);
		   carry=t/10;
		   idx++;
		   if(idx==11 && carry==0)
		      return 1;
		   else   
		      return assign(sum,x,y,z,idx,carry);
		}
		else
		   return 0;
    }
    else if(sum[idx]==' '  &&  carry==0)
    {
    	count++;
        return 1;
    }
    else 
        return 0;    
    
    		      
}


int assignZ(char sum[], char x[], char y[], char z[],int idx, int carry)
{
/* ***********************************************
* Assigns a trial digit value to letter z[idx],
* if needed. Will return 0 if the previously set
* letter-value pairs do not give any puzzle solution.
*
* Uses genCarry() to check if all is good upto
*
*
*
*
*
*
*
*
Assessment Exercise 06
idx. Makes recursive call to assign() to let
that function set letter-value pairs for letters at
locations > idx.
Return status is based on the success or
failure to assign digit value to z[idx] that
delivers a puzzle solution.
**********************************************/
	if(digit[z[idx]]==z[idx]){
	   int i;
	   for(i=0;i<10;i++){
	      if(inuse[i]==0){
	         digit[z[idx]]=i;
	         inuse[i]=1;
	         if(genCarry(sum,x,y,z,idx,carry))
	            return 1;
	         else{
	            digit[z[idx]]=z[idx];
	            inuse[i]=0;
	         }
	      }
	   }
	   return 0;
	}   
	else{
	   return genCarry(sum,x,y,z,idx,carry);
	}
}


int assignY(char sum[], char x[], char y[], char z[],int idx, int carry)
{
/* **********************************************
* Assign digit value to y[idx]. Calls assignZ().
* Called by assignX().
* ***********************************************/
	if(digit[y[idx]]==y[idx]){
	   int i;
	   for(i=0;i<10;i++){
	      if(inuse[i]==0){
	         digit[y[idx]]=i;
	         inuse[i]=1;
	         if(assignZ(sum,x,y,z,idx,carry))
	            return 1;
	         else{
	            digit[y[idx]]=y[idx];
	            inuse[i]=0;
	         }
	      }
	   }
	   return 0;
	}   
	else{
	   return assignZ(sum,x,y,z,idx,carry);
	}
}


int assignX(char sum[], char x[], char y[], char z[],int idx, int carry)
{
/* **********************************************
* Assign digit value to x[idx]. Calls assignY().
* Called by assign().
* ***********************************************/
	if(digit[x[idx]]==x[idx]){
	   int i;
	   for(i=0;i<10;i++){
	      if(inuse[i]==0){
	         digit[x[idx]]=i;
	         inuse[i]=1;
	         if(assignY(sum,x,y,z,idx,carry))
	            return 1;
	         else{
	            digit[x[idx]]=x[idx];
	            inuse[i]=0;
	         }
	      }
	   }
	   return 0;
	}   
	else{
	   return assignY(sum,x,y,z,idx,carry);
	}                  
}


int assign(char sum[], char x[], char y[], char z[],int idx, int carry)
{
/* ************************************************
* Recursive function to assign values to letters in
* the puzzle. It sets digit value for sum[idx] and then
* calls assignX() to set digit values for other letters
*
* The function gets recursive call from assignZ() to
* (recursively) continue work at index idx+1.
*
* Will return 1 if a conbination is found that solves
* the puzzle.
* ****************************************************/
	if(digit[sum[idx]]==sum[idx]){
	  int i;
	  for(i=0;i<10;i++){
	     if(inuse[i]==0){
	        digit[sum[idx]]=i;
	        inuse[i]=1;
	        if(assignX(sum,x,y,z,idx,carry))
	       {
	                printPuzzle(sum, x, y, z);
	           		digit[sum[idx]]=sum[idx];
	           		inuse[i]=0;
	       }
	        else{
	           digit[sum[idx]]=sum[idx];
	           inuse[i]=0;
	        }   
	     }      
	  }
	  return 0;
	}
	else{
	  return (assignX(sum,x,y,z,idx,carry));
	}                  
		
}


int main()
{
/* ***************************************************
* Code provided for training and learning
*
* About 100 lines of code have been remonved from
* this program.
* ***************************************************/
	char two[] = "TWO", three[] = "THREE";
	char seven[] = "SEVEN", twelve[] = "TWELVE";
	/* This can be used to solve another problem*/
	//char two[] = "", three[] = "SEND";
	//char seven[] = "MORE", twelve[] = "MONEY";
	
	char adder[3][11];
	char sum[11];
	int i;
	for (i=0; i<200; i++) digit[i] = i;
	digit[' '] = 0;
	digit['0'] = 0;
	for (i=0; i<11; i++)
	{
	adder[0][i] = ' ';
	adder[1][i] = ' ';
	adder[2][i] = ' ';
	sum[i] = ' ';
	inuse[i] = 0;
	}
	getLetters(two, &adder[0][0]);
	getLetters(three, &adder[1][0]);
	getLetters(seven, &adder[2][0]);
	getLetters(twelve, sum);
	printPuzzle(sum, adder[0], adder[1], adder[2]);
	printf("\n");
	assign(sum, adder[0], adder[1], adder[2], 0, 0);
	if (count)
	{
	printf ("Solutions found: %d\n",count);
	//printPuzzle(sum, adder[0], adder[1], adder[2]);
	}
	else printf("No solution exists\n");
}
