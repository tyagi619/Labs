#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

struct node{
   void *obj;
   long key;
   void *next;
};


struct list{
   struct node *start;
   struct node *end;
};

void *mklist(){
   struct list *QP;
   QP=(struct list *)malloc(sizeof(struct list));
   
   QP->start=NULL;
   QP->end=NULL;
   
   return QP;
}

void push(void *QP,void *elem,long key){
   struct list *lp=(struct list *)QP;
   
   struct node *cur,*prev,*temp;
   temp=(struct node*)malloc(sizeof(struct node));
   cur=lp->start;
   prev=NULL;
   
   if(cur==NULL){
      temp->obj=elem;
      temp->key=key;
      temp->next=NULL;
      lp->start=temp;
      lp->end=temp;
      return;
   }
   
   while(cur!=NULL && cur->key<=key){
      prev=cur;
      cur=cur->next;
   }
   
   if(cur==NULL){
      temp->obj=elem;
      temp->key=key;
      temp->next=NULL;
      prev->next=temp;
      lp->end=temp;
   }
   else if(cur==lp->start){
      temp->obj=elem;
      temp->key=key;
      temp->next=lp->start;
      lp->start=temp;
   }
   else{
      temp->obj=elem;
      temp->key=key;
      temp->next=cur;
      prev->next=temp;
   }
}

void *pop(void *QP,long key){
   struct list *lp=(struct list *)QP;
   
   struct node *cur,*prev,*last,*temp;
   cur=lp->start;
   prev=NULL;
   last=NULL;
   
   if(cur==NULL)
      return NULL;
   prev=cur;
   cur=cur->next;   
      
   while(cur!=NULL && cur->key<=key){
      last=prev;
      prev=cur;
      cur=cur->next;
   }
   
   if(prev->key==key){
      void *L;
      L=prev->obj;
      if(cur==NULL){
         if(last!=NULL){
            lp->end=last;
            last->next=cur;
         }
         else{
            lp->end=NULL;
            lp->start=NULL;
         }      
      }
      else{
         if(last!=NULL){
            last->next=cur;
         }
         else{
            lp->start=cur;
         } 
      }
     
      return L;
   } 
   else if(prev->key!=key){
      void *L;
      if(cur==NULL){
         L=prev->obj;
         if(last!=NULL){
            lp->end=last;
            last->next=cur;
         }
         else{
            lp->end=NULL;
            lp->start=NULL;
         }
         return L;
      }
      else{
         while(cur->next!=NULL){
            prev=cur;
            cur=cur->next;
         }
         L=cur->obj;
         prev->next=NULL;
         lp->end=prev;
         return L;
      }
   }
}               
                        
         
      
         
         
               
   

       
            
                
