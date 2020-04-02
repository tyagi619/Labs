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

node *tree(node *root,int a[],int n1,int b[],int n2){
	
	

int main(){
	node *root=NULL;
	
	int a[11]={8,2,18,7,1,20,81,10,9,3,12};
	int b[11]={18,2,8,3,10,7,81,1,20,9,12};
	
	root=tree(root,a,11,b,11);	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
