#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>

//--------------------------------------------------
//
//починить ввод в dot нескольких слов
//
//-------------------------------------------------

#include "tree.h"

int main()
{
	/*Tree * tree = CreateTree();

	tree->root = CreateNode("ROOT");
	tree->root->left = CreateNode("Left");
	tree->root->left->left = CreateNode("Left_Left");
	tree->root->left->right = CreateNode("Left_Right");
	tree->root->left->right->right = CreateNode("Left_Right_Right");
	tree->root->left->right->right->right = CreateNode("Left_Right_Right_Right");
	tree->root->left->right->left = CreateNode("Left_Right_Left");
	tree->root->right = CreateNode("Right");
	tree->root->right->left = CreateNode("Right_Left");
	tree->root->right->right = CreateNode("Right_Right");

	PrintGraph(tree);
	WriteGraph(tree);
*/
	Tree * one = CreateTree();

	FILE * fileptr = fopen("tree.txt", "r");
	//long long size = FSize(fileptr);

	one->root = ReadGraph(fileptr);
	if(one->root == NULL)
		printf("HERE'S NULL\n");

	fclose(fileptr);
	//WriteGraph(one);

	if(one->root->str == NULL)
		printf("One root NULL\n");

	printf("root = %s\nroot.left = %s\n", one->root->str, one->root->left->str);

	//PrintGraph(one);	

	//printf("end = %d\n", one->amount);
}

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

Node * CreateNode(char * value)
{
	if(!value || value == "\0")
	{
		printf("CreateNode fucked up\n");
		return NULL;
	}

	Node * ptr = (Node *)calloc(1, sizeof(Node));
	if(!ptr)
		return NULL;

	ptr->str = value;
	ptr->left = NULL;
	ptr->right = NULL;
	//ptr->prev = prev;

	return ptr;
}

int CyclePrint(FILE * fileptr, Node * node)
{
	if(!fileptr || !node)
		return -1;
	
	if(node->left)
	{
		fprintf(fileptr, "%s", node->str);
		//fwrite(node->str, sizeof(char), sizeof(node->str), fileptr);
		fprintf(fileptr, " -- ");
		CyclePrint(fileptr, node->left);
	}

	if(node->right)
	{
		fprintf(fileptr, "%s", node->str);
		fprintf(fileptr, " -- ");
		CyclePrint(fileptr, node->right);
	}

	if(!node->right && !node->left)
		fprintf(fileptr, "%s;\n", node->str);

	return 0;
}

int PrintGraph(Tree * point)
{
	if(!point)
		return INCORRECT_ARGUMENT;
	FILE * fileptr = fopen("graph.txt", "w");

	fprintf(fileptr, "graph one{\n");
	CyclePrint(fileptr, point->root);
	fprintf(fileptr, "}\n");
	fclose(fileptr);

	system("dot -Tpng graph.txt -o graph.png");

	return 0;
}

int WriteGraph(Tree * tree)
{
	if(!tree)
		return INCORRECT_ARGUMENT;

	FILE * fileptr = fopen("newtree.txt", "w");
	
	CycleWrite(fileptr, tree->root);

	fclose(fileptr);

	return 0;
}

int CycleWrite(FILE * fileptr, Node * node)
{

	if(!fileptr || !node)
		return INCORRECT_ARGUMENT;

	fprintf(fileptr, "{ ");
	fprintf(fileptr, "%s\n", node->str);

	if(node->left)
		CycleWrite(fileptr, node->left);

	if(node->right)
		CycleWrite(fileptr, node->right);

	fprintf(fileptr, "}\n");

	return 0;
}

int SkipSpace(int * i, char * text)
{
	if(isspace(*(text + *i)))
		while(isspace(*(text + *i)))
			*i += 1;
	return 0;
}

Node * RecRead(char * text, char * word, int * i)
{
	sscanf(text + *i, "%s", word);
	*i += strlen(word) + 1;
	if(strcmp(word ,"{"))
		return NULL;

	sscanf(text + *i, "%s", word);
	*i += strlen(word) + 1;

	Node * node = CreateNode(strdup(word));	

	SkipSpace(i, text);

	node->left = RecRead(text, word, i);
	SkipSpace(i, text);
	node->right = RecRead(text, word, i);
	SkipSpace(i, text);

	sscanf(text + *i, "%s", word);
	*i += strlen(word) + 1;
	if(strcmp(word ,"}"))
		return NULL;

	return node;
}

Node * ReadGraph(FILE * fileptr)
{
	long long size = FSize(fileptr);
	printf("size = %lld\n", size);
	char text[size];
	char word[size];
	int counter = 0;

	if((fread(text, sizeof(char), size, fileptr)) != size)
	{
		printf("fread wasn't completed");
		return NULL;
	}

	return RecRead(text, word, &counter);
}

long long FSize(FILE * ptrfile)
{
	if(ptrfile == NULL)
	{
		perror("Error of file reading");
		return -1;
	}
	long long curroff = ftell(ptrfile);
	fseek(ptrfile, 0, SEEK_END);
	long long size = ftell(ptrfile);
	fseek(ptrfile, curroff, SEEK_SET);
	return size;
}

