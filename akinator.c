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
	one->root = ReadGraph(fileptr);
	if(one->root == NULL)
		printf("HERE'S NULL\n");

	//Search(one->root);

	fclose(fileptr);
	//PrintGraph(one);
	//WriteGraph(one);

	if(one->root->str == NULL)
		printf("One root NULL\n");

	printf("root = %s\nroot.left = %s\n", one->root->str, one->root->left->left->str);
}

Tree * CreateTree()
{
	Tree * point = (Tree *)calloc(ONE, sizeof(*point));
	if(!point)
		return NULL;

	point->root = NULL;
	point->amount = 0;
	return point;
}

void TreeDestroy(Tree * point)
{
	point->amount = 0;
	free(point->root);
	free(point);
}

Node * CreateNode(char * value)
{
	if(value == NULL || value == "\0")
	{
		printf("CreateNode fucked up\n");
		return NULL;
	}

	Node * ptr = (Node *)calloc(ONE, sizeof(*ptr));
	if(!ptr)
		return NULL;

	ptr->str = value;
	ptr->left = NULL;
	ptr->right = NULL;

	return ptr;
}

int CyclePrint(FILE * fileptr, Node * node)
{
	if(!fileptr || !node)
		return -1;
	
	if(node->left)
	{
		fprintf(fileptr, "%s", node->str);
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

int SkipSpace(char ** text)
{
	while(isspace(**text))
		*text += 1;
	return 0;
}

Node * RecRead(char ** text, char * word, char * buff)
{
	for(int j = 0; j < 30; j++)
	{
		word[j] = 0;
		buff[j] = 0;
	}
	int i = 0;
	//printf("RECREAD\n");
	if(sscanf(*text, "%s", word) < 0)
	{
		printf("Bad scanf\n");
		return NULL;
	}
	//printf("WORD = %s\n", word);
	*text += strlen(word) + 1;
	if(strcmp(word ,"{"))
		return NULL;

	while(strcmp(buff, "{}") != 0 && strcmp(buff, "{") != 0)
	{
		//int i = 0;
		if(sscanf(*text, "%s ", word + i) < 0)
		{
			printf("Bad scanf\n");
			return NULL;
		}
		//i += strlen(word + i);
		printf("i = %d\n", i);
		*text += strlen(word + i) + 1;
		i += strlen(word + i);
		sscanf(*text, "%s", buff);
		//printf("wordi = %s wordi + 1 = %s\n", word + i - 1, word + i + 1);
		word[i] = ' ';
		i++;
		//printf("text = %s word = %s, buff = %s\n",*text, strdup(word), buff);
	}
	
	Node * node = CreateNode(strdup(word));	
	printf("new node = %s\n", node->str);

	SkipSpace(text);

	node->left = RecRead(text, word, buff);
	SkipSpace(text);
	printf("left\n");
	node->right = RecRead(text, word, buff);
	SkipSpace(text);
	printf("right\n");

	if(sscanf(*text, "%s", word) < 0)
	{
		printf("Bad scanf\n");
		return NULL;
	}
	*text += strlen(word) + 1;
	if(strcmp(word ,"}"))
		return NULL;

	//printf("end\n");
	return node;
}

Node * ReadGraph(FILE * fileptr)
{
	if(!fileptr)
		return NULL;

	long long size = FSize(fileptr);
	if(!fileptr)
		return NULL;

	printf("size = %lld\n", size);
	char * text = (char *)calloc(size, sizeof(char));
	char * word = (char *)calloc(size, sizeof(char));
	char * buff = (char *)calloc(size, sizeof(char));
	int counter = 0;

	if((fread(text, sizeof(char), size, fileptr)) != size)
	{
		printf("fread wasn't completed");
		return NULL;
	}

	char * _tmp = text;
	Node * root = RecRead(&_tmp, word, buff);

	free(text);
	free(word);
	free(buff);

	return root;  

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

void Search(Node * node)
{
	printf("Is this %s?\nEnter your answer ( y / n )\n", node->str);
	char ans = getchar();
	if(ans == 'y')
		node = node->left;
	else if(node->right)
		node = node->right;
	else 
	{
		char name[512];
		printf("Who is it?\n");

	}
}

