#include <stdio.h>
#include "queue.h"
#include <stdlib.h>
#include <assert.h>



struct node {
   
   void *obj;
   long key;
   struct node *next;
};

struct queue {
   
   struct node *start;
   struct node *end;
};


void *mk(){
   
   struct queue *list;
   list=(struct queue *)malloc(sizeof(struct queue));
   assert(list!=NULL);
   list->start = NULL;
   list->end = NULL;
   
   return list;
}


int size(void *QP){
   struct queue *lp= (struct queue *)QP;
   
   struct node *temp;
   //temp=(struct node*)malloc(sizeof(struct node));
   temp=lp->start;
   
   int count=0;
   while(temp!=NULL){
      count++;
      temp=temp->next;
   }
   return count;
} 

void insert(void *QP,long key,void *elem){
   
   struct queue *lp=(struct queue *)QP;
   
   struct node *curr;
   struct node *prev;
   //curr=(struct node *)malloc(sizeof(struct node));
   //prev=(struct node *)malloc(sizeof(struct node));
   
   curr=lp->start;
   prev=NULL;
   if(curr==NULL){
      add_end(lp,elem,key);
      return;
   }  
   while(curr!=NULL &&  curr->key<key){
      prev=curr;
      curr=curr->next;
   }
   
   if(curr==NULL){
      add_end(lp,elem,key);
   }   
   else if(curr->key==key)
      curr->obj=elem;
   else if(curr==lp->start){
      add_start(lp,elem,key);
   }      
   else{
      struct node *temp;
      temp=(struct node *)malloc(sizeof(struct node));
      temp->obj=elem;
      temp->key=key;
      temp->next=curr;
      prev->next=temp;
   }
   return ;
}




void *removeQ(void *QP, long key){
 
   struct queue *lp=(struct queue *)QP;
   
   struct node *curr;
   //curr=(struct node *)malloc(sizeof(struct node));
   struct node *prev;
   //prev=(struct node *)malloc(sizeof(struct node));
   
   curr=lp->start;
   prev=NULL;
   
   while(curr!=NULL && curr->key<key){
      prev=curr;
      curr=curr->next;
   }
   
   if(curr==NULL || curr->key!=key){
      return NULL;
   }
   else{
      void *L;
      L=curr->obj;
      prev->next=curr->next;
      return L;
  }
}           
   
   
      
            
   
void add_start(void *QP,void *elem,long key){
   
   struct queue *lp =(struct queue *)QP;
   
   struct node *temp;
   temp=(struct node*)malloc(sizeof(struct node));
   temp->obj=elem;
   temp->key=key;
   
   
   if(lp->start==NULL){
      lp->end=temp;
      temp->next=NULL;
   }
   else
      temp->next=lp->start;   
   
   lp->start=temp;  
   
}

void add_end(void *QP,void *elem,long key){
   
   struct queue *lp = (struct queue *)QP; 
   
   struct node *temp;
   temp=(struct node*)malloc(sizeof(struct node));
   temp->obj=elem;
   temp->key=key;
   temp->next=NULL;
   
   if(lp->start==NULL)
      lp->start = temp;
   else   
      lp->end->next=temp;
      
   lp->end=temp;   
   
  
}


void *del_start(void *QP){
   struct queue *lp=(struct queue *)QP;
   
   if(lp->start==NULL)
      return NULL;
   
   void *L;
     
   struct node *temp;
   temp=(struct node*)malloc(sizeof(struct node));
   temp=lp->start;
   lp->start=lp->start->next;  
   if(lp->start==lp->end)
      lp->end=NULL;
   
   L=temp->obj;
   free(temp);   
   
   return L;
}


void *del_end(void *QP){
   struct queue *lp=(struct queue *)QP;
   
   if(lp->start==NULL)
      return lp;
      
   void *L;   
      
   struct node *temp;
   temp=(struct node *)malloc(sizeof(struct node));
   temp=lp->start;
   
   struct node *prev;
   prev=(struct node *)malloc(sizeof(struct node));
   prev=NULL;
   
   while(temp!=lp->end){
      prev=temp;
      temp=temp->next;
   }   
   
   lp->end=prev;
   if(prev==NULL)
      lp->start=NULL;
   
   L=temp->obj;
   
   free(temp);
   
   return L;
}


void *duplicate(void *QP){
   
   struct queue *lp=(struct queue *)QP;
   struct node *temp;
   temp=(struct node *)malloc(sizeof(struct node));
   
   struct queue *DKP;
   DKP = (struct queue *)malloc(sizeof(struct queue));
   struct node *cur;
   cur=(struct node *)malloc(sizeof(struct node));
   struct node *prev;
   prev=(struct node *)malloc(sizeof(struct node));
   
   cur=lp->start;
   DKP = mk();
   if(cur==NULL)
      return DKP;
   else{
      add_end(DKP,cur->obj,cur->key);
      while(cur->next!=NULL){
         cur=cur->next;
         add_end(DKP,cur->obj,cur->key);
      }
      return DKP;
   }
}            
   


      


      
               
              
      
         
        
   
    
  
   
             
   

