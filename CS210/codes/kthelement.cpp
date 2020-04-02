#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

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
      if(x>a[j]){
         swap(a,i+1,j);
         i++;
      }   
   }  
   
   swap(a,i,p);
  
   return i;
}       



int f(vector<int>& a,int p,int q,int k){
   if(p>=q)
      return a[p];

   int r=pivot(a,p,q);
   
   if(r==k-1)
      return a[r];
   if(r>(k-1))
      return f(a,p,r-1,k);
   else
      return f(a,r+1,q,k);
}               


int main(){
   int k;
   cin>>k;
   
   vector<int> a;
   cout<<"Enter the array elements or -1 to exit"<<endl;
   
   while(1){
      int x;
      cin>>x;
      if(x==-1){
         
         break;
      }   
      
      a.push_back(x);
     
   }
   
   if(k>a.size()){
       cout<<"Does not exist"<<endl;
       return 0;
   }    
   int ans=f(a,0,a.size()-1,k);
   
   cout<<ans<<endl;
   return 0;
   
}        
