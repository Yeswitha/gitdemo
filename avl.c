#include<stdlib.h>
#include<stdio.h>
#include<string.h>
struct treenode{
    char name[20];
    int height;
    struct treenode *right,*left;
};
typedef struct treenode node;
int height(node *);
int max(int,int);
node *insert(node*,char*);
node *singlerotatewithleft(node *);
node *singlerotatewithright(node *);
node *doublerotatewithleft(node *);
node *doublerotatewithright(node *);
void inorder(node *);
void preorder(node *);
int getbalance(node *);
node *findmin(node *);
node *deleten(node *,char *);
node *search(node*,char *);
node *root=NULL;
void main()
{
    char a[20];char ch;
    //node *root=NULL; 
	node *temp=NULL;
    while(1)
    {
    	printf("\nenter any one: i to insert string , d to delete ,f to find:");
		scanf("\n%c",&ch);
		switch(ch)
		{
			case 'i': printf("\nenter string :");
					  scanf("%s",a);
					  root=insert(root,a);
					  printf("\npreorder:");
					  preorder(root);
					  printf("\ninorder:");
					  inorder(root);
					  break;
			case 'd':printf("enter string to delete:");
					 scanf("%s",a);
					 root=deleten(root,a);
					 printf("preorder:");
					 preorder(root);
					 printf("inorder:");
					 inorder(root);
					 break;
			case 'f':printf("enter string to search:");
					 scanf("%s",a);
					 temp=search(root,a);
					 if(temp!=NULL)
					  printf("string %s found",a);
					 else
					  printf("string %s notfound",a);
					 break;
			default: exit(0);
					
			}
	}

}
node *insert(node *tree,char *a){
    if(tree==NULL){
        tree=(node *)malloc(sizeof(node));
        tree->left=tree->right=NULL;
        strcpy(tree->name,a);
        tree->height=0;
    }
    else if(strcmp(a,tree->name)<0){
        tree->left=insert(tree->left,a);
        if(getbalance(tree)==2)
            if(strcmp(a,tree->left->name)<0)
                tree=singlerotatewithleft(tree);
            else
                tree=doublerotatewithleft(tree);
    }
    else if(strcmp(a,tree->name)>0){
        tree->right=insert(tree->right,a);
        if(getbalance(tree)==-2)
            if(strcmp(a,tree->right->name)>0)
                tree=singlerotatewithright(tree);
            else
                tree=doublerotatewithright(tree);
    }      
    tree->height=max(height(tree->left),height(tree->right))+1;
    return tree;
}
node *singlerotatewithleft(node *k2){  
    node *k1=k2->left;
    k2->left=k1->right;
    k1->right=k2;
    k2->height=max(height(k2->left),height(k2->right))+1;
    k1->height=max(height(k1->left),height(k1->right))+1;
    return k1;
}
node *singlerotatewithright(node *k2){  
    node *k1=k2->right;
    k2->right=k1->left;
    k1->left=k2;
    k2->height=max(height(k2->left),height(k2->right))+1;
    k1->height=max(height(k1->left),height(k1->right))+1;
    return k1;
}
node *doublerotatewithleft(node *k3){
    k3->left=singlerotatewithright(k3->left);
    return singlerotatewithleft(k3);
}
node *doublerotatewithright(node *k3){
    k3->left=singlerotatewithleft(k3->left);
    return singlerotatewithright(k3);
}
int getbalance(node *tree){
    return height(tree->left)-height(tree->right);
}

int height(node *tree){
    if(!tree)        return -1;
    else            return tree->height;
}
int max(int x,int y){        return (x>y?x:y); }
void inorder(node *tree)
{
    if(tree)
    {
        inorder(tree->left);
        printf("%s ",tree->name);
        inorder(tree->right);
    }
}
void preorder(node *tree)
{
    if(tree)
    {
        printf("%s ",tree->name);
        preorder(tree->left);
        preorder(tree->right);
    }
}
node *search(node *tree,char *r)
{
    if(tree)
    {
       if(strcmp(r,tree->name)<0)
            return (search(tree->left,r));
       else if(strcmp(r,tree->name)>0)
             return (search(tree->right,r));
       else
         return tree;
    }   
}
node *deleten(node *tree,char *a){
    node *tmp;
    int balance;
    if(tree==NULL){
        printf("not found to delete!!\n");
        return tree;
    }
    if(strcmp(a,tree->name)<0)
        tree->left=deleten(tree->left,a);
    else if(strcmp(a,tree->name)>0)
        tree->right=deleten(tree->right,a);
    else if (tree->left&&tree->right){
        tmp=findmin(tree->right);
        strcpy(tree->name,tmp->name);
        tree->right=deleten(tree->right,tmp->name);
    }
    else{
        tmp=tree;
        if(tree->left==NULL)
            tree=tree->right;      
        else if(tree->right==NULL)
            tree=tree->left;
        free(tmp);  
    }
    if(tree==NULL)
        return tree;
    balance=getbalance(tree);
    if(balance>1){
        if(getbalance(tree->left)>=0)
            return singlerotatewithleft(tree);
        else
            return doublerotatewithleft(tree);
    }
    if(balance<-1){
        if(getbalance(tree->right)<=0)
            return singlerotatewithright(tree);
        else
            return doublerotatewithright(tree);
    }
    tree->height=max(height(tree->left),height(tree->right))+1;
    return tree;
} 
node *findmin(node *tree)
{
    if(tree)
       while(tree->left!=NULL)
        tree=tree->left;
    return tree;
}
