#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/*Genreal Functions and variable*/

int left(int i){
	return 2*i+1;
}
int right(int i){
	return 2*i+2;
}
int parent(int i){
	if(i%2){
		return i/2;
	}
	else{
		return i/2-1;
	}		
}

void swap(int *A,int i,int j){
	int temp=*(A+i);
	*(A+i)=*(A+j);
	*(A+j)=temp;
}	


/*End of genral functions and variables*/
/*Build Max Heap starts*/

void MaxHeapify(int A[],int i,int heap_size){
	int l=left(i);		
	int r=right(i);
	int largest=i;
	if(l<heap_size && A[l]>A[i]){
		largest=l;
	}
	
	if(r<heap_size && A[r]>A[largest]){
		largest=r;
	}
	
	if(largest!=i){
		swap(A,i,largest);
		MaxHeapify(A,largest,heap_size);
	}
	
}

void BuildMaxHeap(int A[],int heap_size){
 	int p=parent(heap_size-1);
 	int i;
	for(i=p;i>=0;i--){
		MaxHeapify(A,i,heap_size);
	}
}

void BottomToTop_Max(int A[],int i){
	if(i>0 && A[i]>A[parent(i)] ){
		swap(A,i,parent(i));
		BottomToTop_Max(A,parent(i));
	}
}

/*Build MaxHeap Ends here*/
/*Build Max Heap Operations Start*/

void insert1_Max(int *A,int key,int *heap_size){
	(*heap_size)++;
	*(A+(*heap_size)-1)=key;
	BuildMaxHeap(A,*heap_size);
}

void insert2_Max(int *A,int key,int *heap_size){
	(*heap_size)++;
	*(A+(*heap_size)-1)=key;
	BottomToTop_Max(A,(*heap_size)-1);
}

int extractMax(int A[],int *heap_size){
	int max=A[0];
	swap(A,0,(*heap_size)-1);
	(*heap_size)--;
	MaxHeapify(A,0,*heap_size);
	return max;
}

void merge_Max(int A[],int B[],int C[],int *heap_sizeA,int *heap_sizeB,int *heap_sizeC){
	(*heap_sizeC)=(*heap_sizeA)+(*heap_sizeB);
	for(int i=0;i<(*heap_sizeA);i++){
		C[i]=A[i];
	}
	for(int i=0;i<(*heap_sizeB);i++){
		C[i+(*heap_sizeA)]=B[i];
	}		
	BuildMaxHeap(C,*heap_sizeC);
}	

void increaseKey(int *A,int index,int val,int heap_size){
	if(val<0){
		return;
	}	
	*(A+index)+=val;
	BottomToTop_Max(A,index);
}	
	
		

/*BUild Max Heap Operations ENd*/ 
/*Build Min Heap starts*/



void MinHeapify(int A[],int i,int heap_size){
	int l=left(i);		
	int r=right(i);
	int smallest=i;
	if(l<heap_size && A[l]<A[i]){
		smallest=l;
	}
	
	if(r<heap_size && A[r]<A[smallest]){
		smallest=r;
	}
	
	if(smallest!=i){
		swap(A,i,smallest);
		MinHeapify(A,smallest,heap_size);
	}
	
}

void BuildMinHeap(int A[],int heap_size){
 	int p=parent(heap_size-1);
	int i;
	for(i=p;i>=0;i--){
		MinHeapify(A,i,heap_size);
	}
}

void BottomToTop_Min(int A[],int i){
	if(i>0 && A[i]<A[parent(i)] ){
		swap(A,i,parent(i));
		BottomToTop_Min(A,parent(i));
	}
}

/*Build Min Heap Ends here*/
/*Build Min heap operations start here*/

void insert1_Min(int *A,int key,int *heap_size){
	(*heap_size)++;
	*(A+(*heap_size)-1)=key;
	BuildMinHeap(A,*heap_size);
}

void insert2_Min(int *A,int key,int *heap_size){
	(*heap_size)++;
	*(A+(*heap_size)-1)=key;
	BottomToTop_Min(A,(*heap_size)-1);
}

int extractMin(int A[],int *heap_size){
	int max=A[0];
	swap(A,0,(*heap_size)-1);
	(*heap_size)--;
	MinHeapify(A,0,*heap_size);
	return max;
}

void merge_Min(int A[],int B[],int *C,int *heap_sizeA,int *heap_sizeB,int *heap_sizeC){
	(*heap_sizeC)=(*heap_sizeA)+(*heap_sizeB);
	for(int i=0;i<(*heap_sizeA);i++){
		*(C+i)=A[i];
	}
	for(int i=0;i<(*heap_sizeB);i++){
		*(C+i+(*heap_sizeA))=B[i];
	}
	BuildMinHeap(C,*heap_sizeC);
}	

void decreaseKey(int *A,int index,int val,int heap_size){
	if(val>0){
		return;
	}	
	*(A+index)-=val;
	BottomToTop_Min(A,index);
}

/*Build Min heap operations end here*/			


/*Building Testcases*/

int main(){
	int heap_sizeA=0;
	int heap_sizeB=0;
	int A[100];
	int B[100];
	srand(time(0));
	for(int i=1;i<=10;i++){
		insert2_Max(A,rand()%20,&heap_sizeA);
	}
	for(int i=1;i<=5;i++){
		insert2_Max(B,rand()%20,&heap_sizeB);
	}
	
	for(int i=0;i<=9;i++){
		printf("%d ",A[i]);
	}
	printf("\n");
	for(int i=0;i<4;i++){
		printf("%d ",B[i]);
	}
	printf("\n");
	int C[100];
	int heap_sizeC=0;
	merge_Max(A,B,C,&heap_sizeA,&heap_sizeB,&heap_sizeC);
	
	int r=heap_sizeC;
	for(int i=0;i<=r;i++)
		printf("%d ",extractMax(C,&heap_sizeC));	
	
	printf("\n");
	return 0;
}	

























					
	
