#ifndef TREE_H_
#define TREE_H_


typedef struct node
{
	int value;
	node * left;
	node * right;
	node * prev;
}Node;

typedef struct root
{
	int value;
	node * left;
	node * right;
}Root;

typedef struct tree
{
	Root * root;
	int amount;
}Tree;

Tree * CreateTree();
void TreeDestroy(Tree * point);
Root * CreateRoot(int value);
Node * CreateNode(int value);

#endif