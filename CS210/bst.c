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

node *insert(node *root,int key){
	node *p=root;
	node *prev=NULL;
	node *newNode;
	newNode=makeNode();
	newNode->data=key;
	if(p==NULL){
		root=newNode;
		return root;
	}	
	while(p!=NULL){
		prev=p;
		if(key<=p->data){
			p=p->left;
		}
		else{
			p=p->right;
		}
	}
	
	if(key<=prev->data){
		prev->left=newNode;
	}
	else{
		prev->right=newNode;
	}
	
	
	return root;
}	

node *succesor(node *p){
	node *temp=p->right;
	while(temp->left!=NULL){
		temp=temp->left;
	}
	
	return temp;
}		

node *delete(node *root,int key){
	node *p=root;
	node *prev=NULL;
	if(p==NULL){
		return NULL;
	}
	while(p!=NULL && p->data!=key){
		prev=p;
		if(key<=p->data){
			p=p->left;
		}
		else{
			p=p->right;
		}	
	}
	
	if(p==NULL){
		return root;
	}
	
	if(prev==NULL){
		
		if(p->left==NULL){
			root=p->right;
			free(p);
		}
		else if(p->right==NULL){
			root=p->left;
			free(p);
		}
		else{
			
			node *s=succesor(p);
			printf("%d\n",s->data);
			int k=s->data;
			root=delete(root,s->data);
			p->data=k;
		}
		return root;
	}	
	if(prev!=NULL){
	
		if(p->left==NULL){
			if(prev->left==p){
				prev->left=p->right;
			}
			else{
				prev->right=p->right;
			}
			free(p);
		}
		else if(p->right==NULL){
			if(prev->left==p){
				prev->left=p->left;
			}
			else{
				prev->right=p->left;
			}
			free(p);
		}
		else{
			node *s=succesor(p);
			int k=s->data;
			root=delete(root,s->data);
		}
		return root;
	}
}			
							
					

void inorder(node *root){
	node *cur;
	cur=root;
	if(cur!=NULL){
		
		inorder(cur->left);
		printf("%d ",cur->data);
		inorder(cur->right);
	}
}

int main(){
	node *root;
	root =makeNode();
	root=NULL;
	

	
	char L='L';
	char R='R';
	root=insert(root,18);
	root=insert(root,2);
	root=insert(root,8);
	root=insert(root,3);
	root=insert(root,10);
	root=insert(root,12);
	root=insert(root,7);
	root=insert(root,9);
	root=insert(root,81);
	root=insert(root,1);
	root=insert(root,20);
	
	//root=delete(root,1);
	root=delete(root,20);
	

	inorder(root);
	printf("\n");
	
	return 0;
}
