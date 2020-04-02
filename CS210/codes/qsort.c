#include <stdio.h>


void swap(int*x,int*y){
int temp;
temp=*x;
*x=*y;
*y=temp;
}

int abc=0;
int* split(int *begin,int *end){
  int *p=begin;
  int *pp;
  int i=0;
  for(pp=begin+1;pp<end;pp++)
  {
      if(*pp>*p && (pp!=end-i))
      {
      	/*if(*pp==*(end-i))
      		i++;
        else
        {*/
            swap(pp,end-i);
            i++;
            pp--;
        //}
       }
       if(pp==end-i)
       break;
  }
  if(*p>*(pp)){
      swap(p,pp);
      return pp;
  }
  else{
  swap(p,pp-1);
  return pp-1;
  }
}

void sort(int *begin,int *end){
if(begin<end){
     int *mid;
     mid=split(begin,end);
    // if(mid>begin)
     	sort(begin,mid-1);
     //if(mid<end)
     	sort(mid+1,end);
     }
}

int main()
{
int data[] = {9, 10, 5, 7, 8, 0, 9, 6, 4, 2, 6, 0, 2, 9, 3, 2, 8, 8, 7, 7};
int *begin, *end;
begin = data;
end = begin+19;
while (begin <= end)
{
printf("%d ", *begin);
begin++;
}
printf("\n");
begin = data;
sort(begin, end);
while (begin <= end)
{
printf("%d ", *begin);
begin++;
}
printf("\n");
}

