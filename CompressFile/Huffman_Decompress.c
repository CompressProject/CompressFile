#include "Huffman_Decompress.h"
#include "DataStructuresHuffman.h"
void decompressHuffman(char* decompressionPath)
{
	int res = 1, bitCount = 0;
	FILE* decompressionFile = fopen(decompressionPath, "rb");
	FILE* intermediateFile = fopen("intermediate.bin", "wb");
	if (!decompressionFile || !intermediateFile)
	{
		printf("unable to open the file.");
		exit(1);
	}
	fseek(decompressionFile, 1, SEEK_SET);
	MinHeapNode* root = buildCodeTree(decompressionFile);
	MinHeapNode* currentNode = root;
	char nextCharacter, prevData = ' ';
	int combineData=0,shiftLength;
	if (root == NULL || isLeaf(currentNode)) {
		printf("\nERROR!!\n THE TREE ISNT WORKING!\n");
		return;
	}
	//res = fread(&nextCharacter, sizeof(char), 1, decompressionFile);
	//fseek(decompressionFile, nextCharacter + 2, SEEK_SET);
	while (res)
	{
		res = fread(&nextCharacter, sizeof(char), 1, decompressionFile);
		for (int i = 0; i < (LENGTH_READ_CODE * 8) / LENGTH_CODE_IN_BIT; i++)
		{
			bitCount++;
			if (isLeaf(currentNode))
			{
				printf("nextCharacter&1= %d\n ", nextCharacter & 1);
				printf("currentNode->data%c \n", currentNode->data);
				printf("prevData%c \n", prevData);
				shiftLength = currentNode->data - '0' > 7 ? 4 : 3;
				combineData = combineTwoNumbers(currentNode->data - '0', combineData, shiftLength);
				printf("combineData= %d\n ", combineData);
				if (bitCount == LENGTH_CODE * 2)
				{
					//write to the intermediateFile file.
					fwrite(&combineData, LENGTH_READ_CODE, 1, intermediateFile);
					bitCount = 0;
				}
				//fputc(currentNode->data, intermediateFile);
				printf("currentNode->data= %c \n", currentNode->data);
				currentNode = root;
			}
			if ((nextCharacter & 1) == 0)
				currentNode = currentNode->left;
			else if ((nextCharacter & 1) == 1)
				currentNode = currentNode->right;
			nextCharacter >>= 1;
		}
	}
}
//void writeTreeToDecompressFile(FILE* decompressFile, MinHeapNode* root)
//{
//	if (!root)
//		return;
//	fwrite(root->data, sizeof(char), 1, decompressFile);
//	writeTreeToDecompressFile(decompressFile, root->left);
//	writeTreeToDecompressFile(decompressFile, root->right);
//}

//MinHeapNode* buildCodeTree(FILE* file) {
//	MinHeapNode* root = (MinHeapNode*)malloc(sizeof(MinHeapNode*));
//	char currentCharacter;
//	while ((currentCharacter = fgetc(file)) != '$')
//	{
//		newNode(currentCharacter, 0);
//	}
//	return root;
//}
void buildCodeTreeRec(FILE* file, MinHeapNode* root)
{
	MinHeapNode* node;
	char currentCode[3 * sizeof(char)];
	currentCode[2] = '\0';
	fread(currentCode, sizeof(char), 2, file);
	//if (strcmp(currentCode, "$") == 0)
	//	return;
	if (strcmp(currentCode, "11") == 0)
	{
		strcpy(currentCode, " ");
		fread(currentCode, sizeof(char), 1, file);
		root->data = currentCode[0];
		return;
	}
	if (strcmp(currentCode, "01") == 0)
	{
		node = newNode(currentCode, 0);
		root->left = node;
		buildCodeTreeRec(file, root->left);
	}
	fread(currentCode, sizeof(char), 2, file);
	if (strcmp(currentCode, "10") == 0)
	{
		node = newNode(currentCode, 0);
		root->right = node;
		buildCodeTreeRec(file, root->right);
	}
}
MinHeapNode* buildCodeTree(FILE* file) {
	MinHeapNode* root = (MinHeapNode*)malloc(sizeof(MinHeapNode*));
	root = newNode(' ', 0);
	buildCodeTreeRec(file, root);
	return root;
}