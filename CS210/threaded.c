#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


typedef struct _node{
	int data;
	struct _node *left;
	struct _node *right;
	bool rightthread;
}node;

node* makeNode(){
	node * newNode;
	newNode=(node*)malloc(sizeof(node));
	
	newNode->left=NULL;
	newNode->right=NULL;
	
	newNode->rightthread=false;
	return newNode;
}	

node *search(node *root,int par){
	node *temp;
	temp=root;
	
	if(temp==NULL){
		return NULL;
	}
	
	if(temp->data==par){
		return temp;
	}
	
	node *p;
	p=search(temp->left,par);
	if(p!=NULL){
		return p;
	}
	else{
		if(temp->rightthread==false){
			return search(temp->right,par);
		}
		else{
			return NULL;
		}		
	}
}

node *insert(node *root,int par,int child,char x){
	
	node *newNode;
	newNode=makeNode();
	newNode->data=child;
	
	if(par==-1){
		root=newNode;
		return root;	
	}
	node *p;
	p=search(root,par);
		
	if(p==NULL){
		printf("Parent Element Not Found\n");
		return root;
	}
	
	
	if(x=='L'){
		newNode->right=p;
		p->left=newNode;
		newNode->rightthread=true;
	}
	else if(x=='R'){
		newNode->right=p->right;
		p->right=newNode;
		p->rightthread=false;
		newNode->rightthread=true;
	}
	
	return root;
}

void inorder(node *root){
	node *p;
	p=root;
	node *q;
	do{
		q=NULL;
		while(p!=NULL){
			q=p;
			p=p->left;
		}
		if(q!=NULL){
			printf("%d ",q->data);
			p=q;
			p=p->right;
			while(q->rightthread && p!=NULL){
				printf("%d ",p->data);
				q=p;
				p=p->right;
			}
		}	
	}while(q!=NULL);
}

				

void preorder(node *root){
	node *p;
	p=root;
	node *q;
	do{
		q=NULL;
		while(p!=NULL){
			q=p;
			printf("%d ",q->data);
			p=p->left;
		}
		if(q!=NULL){
			p=q;
			p=p->right;
			while(q->rightthread && p!=NULL){
				q=p;
				p=p->right;
			}
		}	
	}while(q!=NULL);
}

int main(){
	
	node *root;
	root=makeNode();
	root=NULL;
	
	char L='L';
	char R='R';
	
	root=insert(root,-1,18,L);
	
	root=insert(root,18,2,L);
	
	root=insert(root,2,8,L);
	
	root=insert(root,18,3,R);

	root=insert(root,3,10,L);
	
	root=insert(root,3,12,R);
	
	root=insert(root,10,7,L);
	
	root=insert(root,10,9,R);
	
	root=insert(root,7,81,R);
	
	root=insert(root,81,1,L);

	root=insert(root,1,20,R);

	
	inorder(root);
	printf("\n");

	preorder(root);
	printf("\n");

	//postorder(root);
	//printf("\n");

	return 0;
}					
			
				
	
			
	
