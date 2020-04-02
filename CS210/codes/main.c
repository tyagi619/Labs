#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"



int main(){
   
   struct student{
      char name[20];
      char gender[7];
   };
   
   struct queue *male;
   struct queue *female;
   
   
   male=mk();
   female=mk();
   struct student *std;
   int key=0;
  
   while(1){
       std=(struct student *)malloc(sizeof(struct student));
       char s[20];
       char gen[7];
       scanf("%d %s %s",&key,s,gen);
       if(key==0)
         break;
       strcpy(std->name,s);
       strcpy(std->gender,gen);
       if(std->gender[0]=='F')
          insert(female,key,std);
       else
          insert(male,key,std);
       
   }
   
   while(size(male)!=0  && size(female)!=0){
      
      std=(struct student *)del_start(male);
      printf("%s   ",std->name);
      std=(struct student *)del_start(female);
      printf("%s\n",std->name);
      
   }
   
   return 0;
}      
   
   
   
   
   
  
