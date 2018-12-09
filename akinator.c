//--------------------------------------------------
//
//починить ввод в dot нескольких слов
//
//-------------------------------------------------

#include "tree.h"

int main()
{
	Tree * one = CreateTree();

	FILE * fileptr = fopen("tree.txt", "r");
	one->root = ReadGraph(fileptr);

	Search(one->root);
	WriteGraph(one);

	fclose(fileptr);
	return 0;
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
	int i = 0;
	
	CycleWrite(fileptr, tree->root, i);

	fclose(fileptr);

	return 0;
}

int CycleWrite(FILE * fileptr, Node * node, int i)
{
	i++;
	printf("I ============ %d\n", i );
	if(!fileptr || !node)
		return INCORRECT_ARGUMENT;

	fprintf(fileptr, "{ ");
	fprintf(fileptr, "%s ", node->str);

	if(node->left != NULL && node->right != NULL)
		fprintf(fileptr, "\n");

	if(node->left != NULL && node->right == NULL)
		fprintf(fileptr, "\n");	

	if(node->left == NULL && node->right == NULL)
		fprintf(fileptr, "{} {}\n");

	if(node->left == NULL && node->right != NULL)
		fprintf(fileptr, "{}\n");

	if(node->left)
		CycleWrite(fileptr, node->left, i);

	if(node->right == NULL && node->left != NULL)
		fprintf(fileptr, "{}\n");
	
	if(node->right)
		CycleWrite(fileptr, node->right, i);
	
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
	if(sscanf(*text, "%s", word) < 0)
	{
		printf("Bad scanf\n");
		return NULL;
	}
	*text += strlen(word) + 1;
	if(strcmp(word ,"{"))
		return NULL;

	while(strcmp(buff, "{}") != 0 && strcmp(buff, "{") != 0)
	{
		if(sscanf(*text, "%s ", word + i) < 0)
		{
			printf("Bad scanf\n");
			return NULL;
		}
		*text += strlen(word + i) + 1;
		i += strlen(word + i);
		sscanf(*text, "%s", buff);
		word[i] = ' ';
		i++;
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
	do
	{
		char buff[10];
		while(strcmp(buff, "yes") != 0 && strcmp(buff, "no") != 0)
		{
			printf("Is this %s?\nEnter \"yes\" or \"no\"\n", node->str);
			scanf("%s", buff);
			getchar();
		}
		if(strcmp(buff, "yes") == 0)
		{
			printf("YES\n");
			if(node->left)
			{
				node = node->left;
				for(int i = 0; i < 10; i++)
					buff[i] = 0;
			}
			else
			{
				printf("I have said it to you!\n");
				return;
			}
		}
		if(strcmp(buff, "no") == 0)
		{
			printf("NO\n");
			if(node->right)
			{
				node = node->right;
				for(int i = 0; i < 10; i++)
					buff[i] = 0;
			}
			else
			{
				printf("There no such character\n");
				NodeChange(node);
				return;
			}
		}
	}
	while(node);
}

void NodeChange(Node * node)
{
	char pers[50] = " ";
	char diff[60] = " ";
	printf("Who is it?\n");
	fgets(pers, 50, stdin);
	node->right = CreateNode(node->str);
	node->left = CreateNode(strdup(pers));
	printf("What is a difference between %s and %s?\n", node->str, strdup(pers));
	fgets(diff, 60, stdin);
	node->str = strdup(diff);
}

