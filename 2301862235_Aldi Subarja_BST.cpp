#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct data{
	char name[30];
	int age;
	struct data *left, *right;
};


struct data *newData(char *name, int age){
	struct data	*temp = (struct data*)malloc(sizeof(struct data));
	strcpy(temp->name, name);
	temp->age = age;
	temp->right = temp->left = NULL;
	return temp;
}

struct data *push(struct data *root, char *name, int age){
	if(root==NULL) return newData(name, age); 
	if(strcmp(name, root->name) < 0) root->left = push(root->left, name, age);
	else if(strcmp(name, root->name) > 0) root->right = push(root->right, name, age);
	return root;
}

void inorder(struct data *root){
	if(root!=NULL){
		inorder(root->left);
		printf("Name: %-15s | Umur: %d |\n", root->name, root->age);
		inorder(root->right);
	}
}

struct data *deleteData(struct data *root, char name[]){
	if(root == NULL)
		return root;
	else if(strcmp(name, root->name) < 0)
		root->left = deleteData(root->left, name);
	else if(strcmp(name, root->name) > 0)
		root->right = deleteData(root->right, name);
	else{
		if(root->left == NULL || root->right == NULL){
			struct data *temp = root->left != NULL?
						 root->left : root->right;
			if(temp != NULL){
				*root = *temp;
			}
			else{
				temp = root;
				root = NULL;
			}
			free(temp);
		}
		else{
			struct data *temp = root->left;
			
			while(temp->right != NULL)
				temp = temp->right;
				
			strcpy(root->name, temp->name);
			
			root->left = deleteData(root->left, temp->name);
		}
		return root;
	}
}

struct data *deleteAll(struct data *root){
	if(root != NULL){
		deleteAll(root->left);
		deleteAll(root->right);
		free(root);
	}
	return NULL;
}

int main(){
	
	int menu;
	struct data *root = NULL;
	char nama[30];
	
	do{
		for(int i=0;i<30;i++){
			printf("\n");
		}
		printf("1. Input\n");
		printf("2. View\n");
		printf("3. Delete\n");
		printf("4. Exit\n");
		printf(">> ");
		scanf("%d",&menu); getchar();
		switch(menu){
			case 1:
				int umur;
				printf("Masukan nama: ");
				scanf("%[^\n]",nama); getchar();
				printf("Masukan umur: ");
				scanf("%d",&umur); getchar();
				root = push(root,nama,umur);
				break;
			case 2:
				inorder(root);
				getchar();
				break;
			case 3:
				scanf("%[^\n]",nama); getchar();
				root = deleteData(root,nama);
				break;
			case 4:
				root = deleteAll(root);
				break;
		}
		
	}while(menu!=4);
	
	return 0;
}
