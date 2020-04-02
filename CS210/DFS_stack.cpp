#include <bits/stdc++.h>

using namespace std;

int time1=0;

struct Edge{
	char x;
	Edge *next;
	Edge(char c){
		x=c;
		next=NULL;
	}
};

struct Queue{
	int x;
	Queue *next;
	Edge *cur;
	Queue(int a){
		x=a;
		next=NULL;
		cur=NULL;
	}
};

struct Node{
	Edge *next;
	char x;
	char colour;
	// int distance;
	// int succesor;
	int start;
	int end;
	Node(char y){
		x=y;
		// succesor=-1;
		next=NULL;
		colour='w';
		// distance=-1;
		start=0;
		end=0;
	}
};

struct List{
	int size;
	Node *arr;
	List(int x){
		size=x;
		arr=(Node *)malloc(x*sizeof(Node));
		Node *temp=new Node('/');
		for(int i=0;i<x;i++){
			arr[i]=*temp;
		}
	}
};

int search(List *head,char u){
	int i=0;
	while(i<head->size && head->arr[i].x!='/'){
		if(head->arr[i].x==u){
			return i;
		}
		i++;
	}
	return i;
}

void MakeGraphD(List *head,char u,char v){
	int l=search(head,v);
	if(l==head->size || head->arr[l].x=='/'){
		head->arr[l].x=v;
	}
	
	l=search(head,u);
	if(l==head->size || head->arr[l].x=='/'){
		head->arr[l].x=u;
	}

	Edge *temp=head->arr[l].next;
	Edge *prev=NULL;
	while(temp!=NULL){
		prev=temp;
		temp=temp->next;
	}

	Edge *E = new Edge(v);
	if(prev==NULL){
		head->arr[l].next=E;
		return;
	}

	prev->next=E;

}

Queue *top=NULL;

Queue *Push(Queue *Q,int s){
	Queue *S=new Queue(s);
	top=S;
	if(Q==NULL){
		Q=S;
		return Q;
	}
	Queue *temp=Q;
	while(temp->next!=NULL){
		temp=temp->next;
	}

	temp->next=S;
	return Q;

}

Queue* Pop(Queue *Q,int *u){
	if(Q==NULL){
		top=NULL;
		return NULL;
	}

	Queue *temp=Q;
	Queue *prev=NULL;

	while(temp->next!=NULL){
		prev=temp;
		temp=temp->next;
	}
	*u=temp->x;
	top=prev;
	if(prev==NULL){
		Q=NULL;
	}
	else{
		prev->next=NULL;
	}

	delete(temp);
	return Q;
}

void DFS(List *head,char s){
	int k=search(head,s);

	Queue *S=new Queue('a');
	S=NULL;
	int i=k;
	int n=head->size;
	do{
		if(head->arr[i].colour=='w'){
			head->arr[i].colour='g';
			head->arr[i].start=++time1;
			S=Push(S,i);
			Edge *temp=head->arr[i].next;
			top->cur=temp;
			while(S!=NULL){
				temp=top->cur;
				if(temp==NULL){
					int z;
					S=Pop(S,&z);
					head->arr[z].colour='b';
					head->arr[z].end=++time1;
				}
				else{
					int j=search(head,temp->x);
					if(head->arr[j].colour=='w'){
						top->cur=temp->next;
						cout<<"("<<head->arr[top->x].x<<","<<head->arr[j].x<<")"<<endl;
						S=Push(S,j);
						head->arr[j].start=++time1;
						head->arr[j].colour='g';
						top->cur=head->arr[j].next;
					}
					else{
						top->cur=temp->next;
					}
				}
			}

		}
		i=(i+1)%n;
	}while(i!=k);

}

int main()
{
	int n;
	cin>>n;

	List *head = new List(n);

	int m;
	cin>>m;

	char u,v;
	for(int i=0;i<m;i++){
		cin>>u>>v;
		MakeGraphD(head,u,v);
	}
	cout<<endl<<"Enter Source Node: ";
	char s;
	cin>>s;


	DFS(head,s);
	
	cout<<endl;
	for(int i=0;i<n;i++){
		cout<<head->arr[i].x<<" "<<head->arr[i].start<<" "<<head->arr[i].end<<endl;
	}

	return 0;
}