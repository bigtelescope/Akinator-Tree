/*	сделай print_graph
	разберись с graphviz'ом
*/
#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

Tree * CreateTree()
{
	Tree * point = (Tree *)calloc(1, sizeof(Tree));
	if(!point)
		return NULL;

	point->root = NULL;
	point->amount = 0;
	return point;
}

void TreeDestroy(Tree * point)
{
	free(point->root);
	point->amount = 0;
}

Root * CreateRoot(int value)
{
	Root * point = (Root *)calloc(1, sizeof(Root));
	if(!point)
		return NULL;

	point->left = NULL;
	point->right = NULL;
	point->value = value;
	return point;
}

Node * CreateNode(int value)
{
	Node * point = (Node *)calloc(1, sizeof(Node));
	if(!point)
		return NULL;

	point->left = NULL;
	point->right = NULL;
	point->prev = NULL;
	point->value = value;
	return point;
}

int main()
{
	Tree * ptr = CreateTree();
	printf("Ok amount = %d\n", ptr->amount);
}