#ifndef TREE_H_
#define TREE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>

/*
#define TAB() do 							\
		{									\
			for(int j = 0; j < i; j++)			\
				fprintf(fileptr, "\t");		\
		} while (1)	
*/			

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

enum NAMES
{
	INCORRECT_ARGUMENT 	= -1,
	ONE					= 1
};

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
int CycleWrite(FILE *, Node *, int );

long long FSize(FILE * ptrfile);

// Reads graph from file
Node * ReadGraph(FILE *);
Node * RecRead(char **, char *, char *);
int SkipSpace(char **);

void Search(Node *);
void NodeChange(Node *);
void CreatePers(Node *);

#endif