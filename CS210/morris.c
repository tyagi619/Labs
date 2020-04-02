#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _node{
	int data;
	struct _node *left;
	struct _node *right;
}node;
	

node * makeNode(){
	node *newNode;
	newNode=(node *)malloc(sizeof(node));
	newNode->left=NULL;
	newNode->right=NULL;
	
	return newNode;
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




void inorder(node *root){
	node *p=root;
	while(p!=NULL){
		
		if(p->left==NULL){
			printf("%d ",p->data);
			p=p->right;
		}
		else{
			node *temp=p->left;
			while(temp->right!=NULL && temp->right!=p){
				temp=temp->right;
			}
			if(temp->right==p){
				temp->right=NULL;
				printf("%d ",p->data);
				p=p->right;
			}
			else{
				temp->right=p;
				p=p->left;
			}		
		}
		
	}
				
				
}


void preorder(node *root){
	node *cur;
	cur=root;
	if(cur!=NULL){
		
		preorder(cur->left);
		printf("%d ",cur->data);
		preorder(cur->right);
	}
}


/*void postorder(node *root){
	node *cur;
	cur=root;
	if(cur!=NULL){
		postorder(cur->left);
		postorder(cur->right);
		printf("%d ",cur->data);
	}
}	*/



int main(){
	node *root;
	root =makeNode();
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
	

	preorder(root);
	printf("\n");
	
	inorder(root);
	printf("\n");
	
	//postorder(root);
	//printf("\n");
	
	return 0;
}	
	
	
	


	
