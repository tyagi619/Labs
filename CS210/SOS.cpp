#include <bits/stdc++.h>

using namespace std;

typedef struct _file{
	string name;
	struct _file *next;
}file;

typedef struct _folder{
	string name;
	struct _folder *left;
	struct _file *right;
	struct _folder *parent;
}folder;

folder * makeFolder(){
	folder *newFolder;
	newFolder=(folder *)malloc(sizeof(folder));
	newFolder->left=NULL;
	newFolder->right=NULL;
	newFolder->parent=NULL;
	
	return newFolder;
}

file * makeFile(){
	file *newFile;
	newFile=(file*)malloc(sizeof(file));
	newFile->next=NULL;
	
	return newFile;
}

folder *createFolder(folder *p,string s){
	folder *newFolder=makeFolder();
	newFolder->name=s;
	newFolder->parent=p;
	p->left=newFolder;
	cout<<"Made "<<s<<" in "<<p->name<<endl;
	
	return newFolder;
}

folder *addFile(folder *p,string s){
	file *newFile=makeFile();
	newFile->name=s;
	if(p->right==NULL){
		p->right=newFile;
		cout<<"Created "<<s<<" in "<<p->name<<endl;
		return p;
	}
	newFile->next=p->right;
	p->right=newFile;
	cout<<"Created "<<s<<" in "<<p->name<<endl;
	return p;
}

folder *deleteFile(folder *p){
	file *temp,*prev;
	temp=p->right;
	if(temp==NULL){
		cout<<"No file found inside "<<p->name<<endl;
		return p;
	}
	prev=NULL;
	while(temp->next!=NULL){
		prev=temp;
		temp=temp->next;
	}
	if(prev==NULL){
		p->right=NULL;
	}
	else{
		prev->next=NULL;
	}
	cout<<"Deleted "<<temp->name<<" from "<<p->name<<endl;
	//free(temp);
	
	return p;
}			

folder *back(folder *p){
	folder *temp;
	temp=p->parent;
	if(temp==NULL){
		cout<<"Cannot back from root"<<endl;
		return p;
	}		
	temp->left=NULL;	
	cout<<"Back from "<<p->name<<endl;
	//free(p);
	return temp;
}	

int main(){
	folder *root;
	root=makeFolder();
	root->name="root";
	folder *pos;
	pos=root;
	string s;
	while(1){
		cin>>s;
		if(s=="-1"){
			break;
		}
		if(s=="CREATE"){
			cin>>s;
			pos=addFile(pos,s);
		}
		else if(s=="DELETE"){
			pos=deleteFile(pos);
		}
		else if(s=="NEW"){
			cin>>s;
			pos=createFolder(pos,s);
		}
		else{
			pos=back(pos);
		}
	}
	
	return 0;						
}					

	

