#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void output(int arr[],int n)
{
   int c;
    for(c=0;c<n;++c)
        printf("%d",arr[c]);
        printf("\n");
}
int digit[200], /* Digit value for char with code of index */
inuse[11]={0};
int t=0; /*Digits already in use. Actually only 10 needed*/
char * getLetters(char *from, char *to)
{
/* ******************************************************
 * Recursive function to move chars in string from 
 * into array to. Reverses order to help align letters
 * in puzzle words on unit position (index 0 in to)
 * *****************************************************/
  int l,c=0;
  for(l=0;from[l]!='\0';++l);
  for(c=0;c<l;++c)
      to[c]=from[l-c-1];
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
    for (i = 10; i>=0; i--)
        if (sum[i] == ' ')
            printf("  ");
        else printf("--");
    printf("\n");
    printOneNum(sum);
    printf("\n");
}
int genCarry (char sum[], char x[], char y[], char z[],
              int idx, int carry)
{
    int t=digit[x[idx]]+digit[y[idx]]+digit[z[idx]]+carry;
    if(x[idx]==' ')   t-=' ';
    if(y[idx]==' ')   t-=' ';
    if(y[idx]==' ')   t-=' ';
    if(t%10==digit[sum[idx]])
    {
        carry=t/10;       
        if(sum[idx+1]==' ')
            return 1;
        else return(assign(sum,x,y,z,idx+1,carry));
    }
   
    else return 0;
}
int assignZ(char sum[], char x[], char y[], char z[],
            int idx, int carry)
{
    /* ***********************************************
     * Assigns a trial digit value to letter z[idx],
     * if needed. Will return 0 if the previously set
     * letter-value pairs do not give any puzzle solution.
     *  
     * Uses genCarry() to check if all is good upto 
     * idx. Makes recursive call to assign() to let
      that function set letter-value pairs for letters at
     * locations > idx. 
     *
     * Return status is based on the success or
     * failure to assign digit value to z[idx] that
     * delivers a puzzle solution.
     * **********************************************/
   /* if(digit[z[idx]]==z[idx])
    digit[z[idx]]=digit[sum[idx]]-carry-x[idx]-y[idx];
   
    carry=digit[z[idx]]/10;
    digit[z[idx]]%=10;

    if(inuse[digit[z[idx]]])  return 0;
    else inuse[digit[z[idx]]]=1;

    if(genCarry(sum,x,y,z,idx,carry))
    {
        return 1;
    }

    else {inuse[digit[z[idx]]]=0;return 0;}*/
    int c=0;
     if(digit[z[idx]]==z[idx]&&z[idx]!=' ')
     {for(c=0;c<10;++c)
     {
        if(!inuse[c])
        {digit[z[idx]]=c;
        inuse[c]=1;
        if(genCarry(sum,x,y,z,idx,carry))
            break;
        inuse[c]=0;
        }
     }
     if(c==10)  { inuse[c]=0;digit[z[idx]]=z[idx];
     return 0;}
     else return 1;
    }

     else   return genCarry(sum,x,y,z,idx,carry);

}
int assignY(char sum[], char x[], char y[], char z[],
            int idx, int carry)
{
    /* **********************************************
     * Assign digit value to y[idx]. Calls assignZ().
     * Called by assignX().
     * ***********************************************/
     int c=0;
     if(digit[y[idx]]==y[idx]&&y[idx]!=' ')
     {for(c=0;c<10;++c)
     {
        if(!inuse[c])
        {digit[y[idx]]=c;
        inuse[c]=1;
        if(assignZ(sum,x,y,z,idx,carry))
            break;
            inuse[c]=0;
        }
     }
     if(c==10)  { inuse[c]=0;digit[y[idx]]=y[idx];return 0;}
     else return 1;
    }

     else   return assignZ(sum,x,y,z,idx,carry);

}
int assignX(char sum[], char x[], char y[], char z[],
            int idx, int carry)
{
     /* **********************************************
     * Assign digit value to x[idx]. Calls assignY().
     * Called by assign().
     * ***********************************************/
     int c;
     if(digit[x[idx]]==x[idx]&&x[idx]!=' ')
     {
     for( c=0;c<10;++c)
     {
        if(!inuse[c])
        {digit[x[idx]]=c;
        inuse[c]=1;
        if(assignY(sum,x,y,z,idx,carry))
            break;
        inuse[c]=0;
        }
     }
     if(c==10) {inuse[c]=0;digit[x[idx]]=x[idx];return 0;
        
     }
     else return 1;
    }

     else   return assignY(sum,x,y,z,idx,carry);
}
int assign(char sum[], char x[], char y[], char z[],
           int idx, int carry)
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
    int c;
    if(digit[sum[idx]]==sum[idx])
    {
     for(c=0;c<10;++c)
     { 
        if(!inuse[c])
        {digit[sum[idx]]=c;
        inuse[c]=1;
        if(assignX(sum,x,y,z,idx,carry))
            break;
        inuse[c]=0;
        }
     }
    
    
     if(c==10) 
     {inuse[c]=0;digit[sum[idx]]=sum[idx]; return 0;}
     else return 1;
    }

    else{
        return assignX(sum,x,y,z,idx,carry);

    }

}
int main()
{
    char two[] = "TWO", three[] = "THREE";
    char seven[] = "SEVEN", twelve[] = "TWELVE";
    /* This can be used to solve another problem
    char two[] = "", three[] = "SEND";
    char seven[] = "MORE", twelve[] = "MONEY";
    */
    char adder[3][11];
    char sum[11];
    int i;
    for (i=0; i<200; i++) digit[i] = i;
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
    if (assign(sum, adder[0], adder[1], adder[2], 0, 0))
    {
        printf ("Solution found:\n");
        printPuzzle(sum, adder[0], adder[1], adder[2]);
    }
    else{ printf("No solution exists\n");
    printPuzzle(sum, adder[0], adder[1], adder[2]);}
} 
