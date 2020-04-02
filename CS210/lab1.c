#include <stdio.h>
#include <stdlib.h>

typedef struct _Node{
	char data;
	struct _Node * next;
}node;	

typedef struct _Stack{
	node * start;
	node * end;
}stack;	

stack *createStack(){
	stack *st;
	st=(stack*)malloc(sizeof(stack));
	st=NULL;
	return st;
}	

stack *push(stack *st,char x){
	
	node *newNode;
	newNode=(node*)malloc(sizeof(node));
	newNode->data=x;
	
	if(st==NULL){
		newNode->next=NULL;
		st->start=newNode;
		st->end=newNode;
		return st;
	}
	
	newNode->next=NULL;
	st->end=newNode;
	
	return st;
}


stack *pop(stack *st,char *x){
	node *temp,*prev;
	if(st==NULL){
		return NULL;
	}	
	temp=st->start;	
	prev=NULL;
	while(temp!=st->end){
		prev=temp;
		temp=temp->next;
	}
	st->end=prev;
	if(prev==NULL){
		st->start=NULL;
		st=NULL;
	}
	else{
		prev->next=NULL;
	}
	*x=temp->data;	
	free(temp);
	
	return st;
}

stack* check(stack* st){
	if(st==NULL){
		return NULL;
	}
	stack *st1;
	st1=createStack();
	stack *st2;
	st2=createStack();	
	
	int flag;
	if(st->start->data>=48 && st->start->data<=57){
		flag=1;
	}
	else{
		flag=0;
	}
	node *temp;
	temp=st->start;
	
	while(temp!=NULL){
		if(temp->data>=48 && temp->data<=57 && (flag==1 || flag==2)){
			flag=0;
			st2=push(st2,temp->data);
			continue;
		}
		else if( flag==0){
			if(temp->data=='('){
				st1=push(st1,temp->data);
			}
			else if(temp->data==')'){
				if(st1==NULL){
					return NULL;
				}
				
				char a;
				while(st1!=NULL && st1->end->data!='('){
					st1=pop(st1,&a);
					st2=push(st2,a);
				}
				if(st1==NULL){
					return NULL;
				}
				st1=pop(st1,&a);			
			}
			else if(temp->data=='+'){
				if(st1==NULL || st1->end->data=='('){
					st1=push(st1,'+');
				}
				else{
					char a;
					while(st1!=NULL && st1->end->data!='('){
						st1=pop(st1,&a);
						st2=push(st2,a);
					}
					st1=push(st1,'+');
				}
					
			}
			if(temp->data=='-'){
				if(st1==NULL || st1->end->data=='('){
					st1=push(st1,'-');
				}
				else{
					char a;
					while(st1!=NULL && st1->end->data!='('){
						st1=pop(st1,&a);
						st2=push(st2,a);
					}
					st1=push(st1,'-');
				}
				
			}
			if(temp->data=='*'){
				if(st1==NULL || st1->end->data=='(' || st1->end->data=='+' || st1->end->data=='-'){
					st1=push(st1,'*');
				}
				else{
					char a;
					while(st1!=NULL && st1->end->data!='+' && st1->end->data!='(' &&  st1->end->data!='-'){
						st1=pop(st1,&a);
						st2=push(st2,a);
					}
					st1=push(st1,'*');	
				}
			}
			if(temp->data=='/'){
				if(st1==NULL || st1->end->data=='(' || st1->end->data=='+' || st1->end->data=='-' || st1->end->data=='*'){
					st1=push(st1,'/');
				}
				else{
					char a;
					while(st1!=NULL && st1->end->data!='+' && st1->end->data!='(' &&  st1->end->data!='-' && st1->end->data!='*'){
						st1=pop(st1,&a);
						st2=push(st2,a);
					}
					st1=push(st1,'/');	
				}
			}
			if(temp->data=='$'){
				st1=push(st1,'$');
			}
		}	
				
		
					
		



void main(){

	stack *st1;
	st1=createStack();
	stack *st2;
	st2=createStack();
	
	char a;
	a=' ';
	while(a!='\n'){
		scanf("%c",&a);
	}
		
}
