#ifndef TREE_H_
#define TREE_H_

typedef struct node
{
	char * str;
	struct node * left;
	struct node * right;
	struct node * prev;
}Node;

typedef struct tree
{
	Node * root;
	int amount;
}Tree;

//Creates tree
Tree * CreateTree();

//Function for cleaning a memory
void TreeDestroy(Tree *);

//Creates node with certain value
Node * CreateNode(char * value);

//Recursive function for bypassing of a tree for PrintGraph
int CyclePrint(FILE *, Node *);

//Function for making file.dot
int PrintGraph(Tree *);

//Function that writes a structure of a tree
int WriteGraph(Tree *);

//Recursive function for bypassing of a tree for WriteGraph
int CycleWrite(FILE *, Node *);

long long FSize(FILE * ptrfile);

//Node * ReadGraph(FILE *, char *, char*);
Node * ReadGraph(FILE *);

#endif
