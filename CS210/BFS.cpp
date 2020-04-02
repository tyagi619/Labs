#include <bits/stdc++.h>

using namespace std;

struct Queue{
	char x;
	Queue *next;
	Queue(char a){
		x=a;
		next=NULL;
	}
};

struct Edge{
	char x;
	Edge *next;
	Edge(char c){
		x=c;
		next=NULL;
	}
};

struct Node{
	Edge *next;
	char x;
	char colour;
	int distance;
	int succesor;
	Node(char y){
		x=y;
		succesor=-1;
		next=NULL;
		colour='w';
		distance=-1;
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

void MakeGraph(List *head,char u,char v){
	int l=search(head,v);
	if(l==head->size || head->arr[l].x=='/'){
		head->arr[l].x=v;
	}

	Edge *temp=head->arr[l].next;
	Edge *prev=NULL;
	while(temp!=NULL){
		prev=temp;
		temp=temp->next;
	}

	Edge *E = new Edge(u);
	if(prev==NULL){
		head->arr[l].next=E;
	}
	else{
		prev->next=E;
	}	
	
	l=search(head,u);
	if(l==head->size || head->arr[l].x=='/'){
		head->arr[l].x=u;
	}

	temp=head->arr[l].next;
	prev=NULL;
	while(temp!=NULL){
		prev=temp;
		temp=temp->next;
	}

	Edge *A = new Edge(v);
	if(prev==NULL){
		head->arr[l].next=A;
	}
	else{
		prev->next=A;
	}	

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

Queue *ENQUEUE(Queue *Q,char s){
	Queue *S=new Queue(s);
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

Queue* DEQUEUE(Queue *Q,char *u){
	Queue *S=Q;
	*u=S->x;
	//char u=Q->x;
	Q=Q->next;
	return Q;
}

void BFS(List *head,char s){
	int k=search(head,s);
	head->arr[k].distance=0; 
	Queue *Q = new Queue(s);
	Q=ENQUEUE(Q,s);
	while(Q!=NULL){
		char u;

		Q=DEQUEUE(Q,&u);
		//Q=Q->next;
		
		k=search(head,u); 
		Edge *temp=head->arr[k].next;
		while(temp!=NULL){
			int j=search(head,temp->x);
			if(head->arr[j].colour=='w'){
				head->arr[j].colour='g';
				head->arr[j].succesor=k;
				head->arr[j].distance=head->arr[k].distance+1;
				Q=ENQUEUE(Q,temp->x);
			}
			temp=temp->next;
		}
		head->arr[k].colour='b';
	}
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
		MakeGraph(head,u,v);
	}
	cout<<endl<<"Enter Source Node: ";
	char s;
	cin>>s;


	BFS(head,s);
	
	for(int i=0;i<n;i++){
		cout<<head->arr[i].x<<" "<<head->arr[i].distance<<endl;
	}
	
	return 0;
}