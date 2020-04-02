#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

void quicksort(vector<int>& a,int p,int q);
void swap(vector<int>& a, int i,int j);
int pivot(vector<int>& a,int p,int q);

int main(){
   vector<int> a;
   cout<<"Enter data or -1 to exit"<<endl;
   while(1){
      int x;
      cin>>x;
      if(x==-1)
         break;
      
      a.push_back(x);
   }
   
   quicksort(a,0,a.size()-1);
   
   for(int i=0;i<a.size();i++)
       cout<<a[i]<<" ";
       
   cout<<endl;
   return 0;
}


void quicksort(vector<int>& a,int p,int q){
   if(p<q){
      int r=pivot(a,p,q);
      
      quicksort(a,p,r-1);
      quicksort(a,r+1,q);
   }
}


void swap(vector<int>& a, int i,int j){

   int temp;
   temp=a[i];
   a[i]=a[j];
   a[j]=temp;
}   


int pivot(vector<int>& a,int p,int q){
   srand(time(NULL));
   int y=(p+(rand()%(q-p+1)));
   swap(a,y,p);
   int x=a[p];
   
   int i=p;
   for(int j=p+1;j<=q;j++){
      if(x>=a[j]){
         swap(a,i+1,j);
         i++;
      }   
   }  
   
   swap(a,i,p);
  
   return i;
}                     
