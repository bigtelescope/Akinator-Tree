#ifndef AKINATOR_H_
#define AHINATOR_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>

// Structure for tree's node
typedef struct node
{
	char * str;
	struct node * left;
	struct node * right;
	//struct node * prev;
}Node;

typedef struct tree
{
	Node * root;
	//int amount;
}Tree;

enum NAMES
{
	ONE 			= 1,
	INCORRECT_ARGUMENT 	= -1,
	FILE_READING_ERROR	= -2,
	SIZE_DEF_ERROR		= -3,
	EMPTY_FILE		= -4,
	MEM_ALLOC_ERROR 	= -5
};

/*! Defines a size of an input file */
long long FSize(FILE * ptrfile);

/*! Creates tree */
Tree * CreateTree();

/*! Function for cleaning a memory */
void TreeDestroy(Tree *);

/*! Creates node with certain value */
Node * CreateNode(char * value);


/*! Recursive function for bypassing of a tree for PrintGraph() */
int CyclePrint(FILE *, Node *);
/*! Function for making .dot file */
int PrintGraph(Tree *);

/*! Function that writes a structure of a tree into .txt file */
int WriteGraph(Tree *);
/*! Recursive function for bypassing of a tree for WriteGraph() */
int CycleWrite(FILE *, Node *, int );

/*! Reads new graph from .txt file */
Node * ReadGraph(FILE *);
/*! This one is used by ReadGraph() for bypassing of a tree */
Node * RecRead(char **, char *, char *);
/*! This one is used by ReadGraph() for passing of spaces */
int SkipSpace(char **);

/*! Function for searching of an certain person */
void Search(Node *);
/*! Function for adding a new person to a tree */
void NodeChange(Node *);

#endif
