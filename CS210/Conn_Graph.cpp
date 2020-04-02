#include <bits/stdc++.h>

using namespace std;

struct Queue{
	int x;
	Queue *next;
	Queue(int a){
		x=a;
		next=NULL;
	}
};

struct Graph{
	int size;
	int **arr;
	char *colour;
	Graph(int s){
		size=s;
		arr=new int*[s];
		for(int i=0;i<s;i++){
			arr[i]=new int[s];
			for(int j=0;j<s;j++){
				arr[i][j]=0;
			}
		}
		colour=new char[s];
		for(int i=0;i<s;i++){
			colour[i]='w';
		}
	}
};

Queue* ENQUEUE(Queue *Q,int s){
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

Queue* DEQUEUE(Queue *Q,int *u){
	Queue *S=Q;
	*u=S->x;
	Q=Q->next;
	return Q;
}

void BFS(Graph *g,int start,int end){
	Queue *Q=new Queue(start-1);
	int n=g->size;
	while(Q!=NULL){
		int i;
		Q=DEQUEUE(Q,&i);
		g->colour[i]='g';
		for(int j=0;j<n;j++){
			if(g->arr[i][j]==1 && j==end-1){
				cout<<"YES"<<endl;
				return ;
			}
			if(g->arr[i][j]==1 && g->colour[j]=='w'){
				Q=ENQUEUE(Q,j);
				g->colour[j]='g';
			}
		}
		g->colour[i]='b';
	}

	cout<<"NO"<<endl;

}

int main()
{
	int n;
	cin>>n;

	int m;
	cin>>m;

	Graph *g=new Graph(n);

	int u,v;
	for(int i=0;i<m;i++){
		cin>>u>>v;
		g->arr[u-1][v-1]=1;
	}
	int st;
	cout<<endl<<"Enter Starting Node: ";
	cin>>st;

	int ed;
	cout<<endl<<"Enter Ending Node: ";
	cin>>ed;

	BFS(g,st,ed);
	
	cout<<endl;

	return 0;
}