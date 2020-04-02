#include<iostream>
#include<vector>

using namespace std;

int crossmax(vector<int> a,int low,int high,int* min,int* max);
int maxarray(vector<int> a,int low,int high,int *x,int *y);

int main(){
   vector<int> arr;
   
   cout<<"Enter your data or -256 to exit :  "<<'\n';
   
   while(1){
      int x;
      cin>>x;
      if(x==-256)
         break;
      
      arr.push_back(x);
   } 
   int min,max;
   
   int max_sum=maxarray(arr,0,arr.size()-1,&min,&max);
   
   for(int i=0;i<arr.size();i++)
      cout<<arr[i]<<" ";
      
   cout<<'\n'<<max_sum<<'\n';  
   cout<<"from : "<<min<<" ------ to : "<<max<<endl; 
      
   return 0;
}  


int crossmax(vector<int> a,int low,int high,int *min,int *max){
   int mid=(low+high)/2;
   int leftval=-256;
   int sum=0;
   for(int i=mid;i>=low;i--){
      sum+=a[i];
      if(sum>leftval){
         *min=i;
         leftval=sum;
      }   
   }
   sum=0; 
   int rightval=-256;
   for(int i=(mid+1);i<=high;i++){
      sum+=a[i];
      if(sum>rightval){
         *max=i;
         rightval=sum;
      }   
   }
   
   return (leftval+rightval);
}              


int maxarray(vector<int> a,int low,int high,int *x,int *y){
   if(low==high){
      *x=low;
      *y=high;
      return a[low];
   }   
      
   int mid=(low+high)/2;
   
   int left_min,left_max;
   int left=maxarray(a,low,mid,&left_min,&left_max);
   
   int right_min,right_max;
   int right=maxarray(a,mid+1,high,&right_min,&right_max);
   
   int cross_min,cross_max;
   int cross=crossmax(a,low,high,&cross_min,&cross_max);
   
   if(left>=right && left>=cross){
      *x=left_min;
      *y=left_max;
      return left;
   }   
   else if(right>=left && right>=cross){
      *x=right_min;
      *y=right_max;
      return right;
   }   
   else{
      *x=cross_min;
      *y=cross_max;
      return cross;
   }   
}                   
        
