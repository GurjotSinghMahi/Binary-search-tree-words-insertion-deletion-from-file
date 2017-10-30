#include <iostream>
#include <cstring>
#include <string>

using namespace std;

struct tree
{
	char word[30];
	struct tree *left, *right;
};
typedef struct tree *TREE;

TREE root=NULL;
int flag=1;

struct tree* cell_creation(char *val)
{
	struct tree *p=(TREE)malloc(sizeof(struct tree));
	strcpy(p->word, val);
	p->left=NULL;
	p->right=NULL;
	return p;
}

struct tree* insert(tree *node, char *word)
{
	if(node==NULL)
	{
		if (flag == 1)
		{
			root = cell_creation(word);
			flag--;
		}
		else
		{
			return cell_creation(word);
		}
		
	}
	
	else
	{
		if(strcmp(word, node->word)<0)
		{
			node->left  = insert(node->left, word);
		}	
		else if(strcmp(word, node->word)>0)
		{
	    		node->right = insert(node->right, word);
		}
	}

return node;
}

struct tree* findmininum(struct tree *temp)
{

	if (temp==NULL)
	{
		return NULL;
	}
	
	while(temp->left != NULL)
	{
		temp = temp->left;
	}
return temp;
}

tree* maximumKey(tree* ptr)
{
	while(ptr->right != NULL) {
		ptr = ptr->right;
	}
	return ptr;
}

void deleteNode(tree* &root, char *key)
{
	if (root == NULL)
	{
		cout << "<-(not in BST)"<<endl;	
		return;
	}

	if(strcmp(key, root->word)<0)
		deleteNode(root->left, key);

   	else if(strcmp(key, root->word)>0)
		deleteNode(root->right, key);

	else
	{
		if (root->left == NULL && root->right == NULL)
		{
			delete root;
			root = NULL;
		}
		else if (root->left && root->right)
		{
			tree *predecessor = maximumKey(root->left);
			strcpy(root->word,predecessor->word);
			deleteNode(root->left, predecessor->word);
		}
		else
		{
           		tree* child = (root->left)? root->left: root->right;
			tree* curr = root;
			root = child;
			delete curr;
		}
	}
}
int maxDepth(struct tree* node) 
{
   if (node==NULL) 
       return 0;
   else
   {
       int lDepth = maxDepth(node->left);
       int rDepth = maxDepth(node->right);
 
       if (lDepth > rDepth) 
           return(lDepth+1);
       else return(rDepth+1);
   }
} 

void printGivenLevel(struct tree* root, int level)
{
	if (root == NULL)
	{return;}

	if (level == 1)
	{
	cout << root->word << " ";
	}

	else if (level > 1)
	{
		printGivenLevel(root->left, level-1);
		printGivenLevel(root->right, level-1);
	}
}

int main()
{

FILE *file1;
file1 = fopen("insertion_file.txt","r");
char word[30];
while(fscanf(file1,"%s",word)==1)
{
	insert(root, word);		
}
fclose(file1);

int c = maxDepth(root);
cout << "Levels after insertion in Binary search Tree:"<< endl;
for (int j =1;j<=c;j++)
{
printGivenLevel(root, j);cout << endl;
}

cout << endl;


file1 = fopen("deletion_file.txt","r");
char words[30];
cout << "Word being deleted is: " << endl;
while(fscanf(file1,"%s",words)==1)
{
	cout << words << " ";
	deleteNode(root, words);
}
cout << endl;
fclose(file1);
cout << endl;
cout << "Levels after deletion in Binary search Tree:"<< endl;
int d = maxDepth(root);
for (int j =1;j<=d;j++)
{
printGivenLevel(root, j); cout << endl;
}

return 0;
}

