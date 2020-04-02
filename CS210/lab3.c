#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _node{
	int data;
	struct _node *left;
	struct _node *right;
}node;

typedef struct _stack{
	node *elem;
	struct _stack *next;
}stack;

stack *makeStack(){
	stack *newStack;
	newStack=(stack *)malloc(sizeof(stack));
	newStack->elem=NULL;
	newStack->next=NULL;
}	

node * makeNode(){
	node *newNode;
	newNode=(node *)malloc(sizeof(node));
	newNode->left=NULL;
	newNode->right=NULL;
	
	return newNode;
}

bool isEmpty(stack *s){
	if(s==NULL){
		return true;
	}
	return false;
}			

stack *push(stack *s,node *p){
	stack *newNode;
	newNode=makeStack();
	newNode->elem=p;
	if(s==NULL){
		s=newNode;
		return s;
	}
	
	newNode->next=s;
	s=newNode;
	
	return s;
}

stack *pop(stack *s,node **p){
	if(s==NULL){
		return NULL;
	}
	stack *temp;
	temp=s;
	s=temp->next;
	*p=temp->elem;
	
	free(temp);
	return s;
}				

node *insert(node *root,int par,int child,char dir){
	node *cur;
	node *newNode;
	newNode=makeNode();
	newNode->data=child;
	cur=root;
	if(par==-1){
		root=newNode;
		return root;
	}
	if(cur==NULL){
		return NULL;
	}		
	
	if(cur->data==par){
		if(dir=='L'){
			cur->left=newNode;
		}
		else{
			cur->right=newNode;
		}
		return root;
	}
	insert(cur->left,par,child,dir);
	insert(cur->right,par,child,dir);
	
	return root;
}


void inorder1(node *root){
	node *cur;
	cur=root;
	if(cur!=NULL){
		inorder1(cur->left);
		printf("%d ",cur->data);
		inorder1(cur->right);
	}
}

void inorder2(node *root,stack *s){
	node *temp;
	temp=root;
	do{
		while(temp!=NULL){
			s=push(s,temp);
			temp=temp->left;
		}
		node *p;
		s=pop(s,&p);
		printf("%d ",p->data);
		temp=p->right;
	}while(!isEmpty(s) || temp!=NULL);
}		
			

void preorder1(node *root){
	node *cur;
	cur=root;
	if(cur!=NULL){
		printf("%d ",cur->data);
		preorder1(cur->left);
		preorder1(cur->right);
	}
}

void preorder2(node *root,stack *s){
	node *temp;
	temp=root;
	do{
		while(temp!=NULL){
			s=push(s,temp);
			printf("%d ",temp->data);
			temp=temp->left;
		}
		node *p;
		s=pop(s,&p);
		temp=p->right;
	}while(!isEmpty(s) || temp!=NULL);
}

void postorder1(node *root){
	node *cur;
	cur=root;
	if(cur!=NULL){
		postorder1(cur->left);
		postorder1(cur->right);
		printf("%d ",cur->data);
	}
}	

void postorder2(node *root,stack *s){
	node *temp;
	temp=root;
	do{
		
		while(temp!=NULL){
			s=push(s,temp);
			temp=temp->left;
		}
		
		temp=s->elem->right;
		node *p;
		if(temp==NULL && !isEmpty(s)){
			
			do{
				
				s=pop(s,&p);
				printf("%d ",p->data);
			}while(!isEmpty(s) && (s->elem->right==NULL || s->elem->right==p));
			if(isEmpty(s)){
				temp=NULL;
			}
			else{
				temp=s->elem->right;
			}			
		}	
			
	}while(!isEmpty(s) || temp!=NULL);
}

int main(){
	node *root;
	root =makeNode();
	root=NULL;
	
	stack *s;
	s=makeStack();
	s=NULL;
	
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
	
	inorder1(root);
	printf("\n");
	inorder2(root,s);
	printf("\n");
	preorder1(root);
	printf("\n");
	preorder2(root,s);
	printf("\n");
	postorder1(root);
	printf("\n");
	postorder2(root,s);
	printf("\n");
	return 0;
}	
	
	
	


	
