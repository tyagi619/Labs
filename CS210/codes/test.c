#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"


int main(){
   
   struct student{
      char name[30];
      //int roll;
   };
   
   struct list *Q;
   
   Q=mklist();
   
   struct student *std;
   
   long key;
   int i;
   FILE *fp;
   fp=fopen("a.txt","r");
   while(1){
      std=(struct student *)malloc(sizeof(struct student));
      char s[30];
      fscanf(fp,"%d ",&i);
      if(i==0){
      break;
      }
      fscanf(fp,"%[^\n]s",s);
      //scanf("%ld",&key);
      //if(key==-1)
        // break;
      //scanf("%s %d",s,&i);   
      strcpy(std->name,s);
      //std->roll=i;
      
      push(Q,std,i);
   }
   fclose(fp);
   while(1){
      printf("Enter the key you want to search : ");
      scanf("%ld",&key);
      if(key==-1)
         break;
      void *L;
      L=pop(Q,key);
      if(L!=NULL){   
         std=(struct student *)L;
         printf("%s\n",std->name);
      }
      else {
         printf("The list is Empty");
         break;   
      }   
   }
   
   printf("\n");
   return 0;
}              
