#include "Huffman_Compress.h"
typedef struct Code
{
	int* codeArray;
	int count;
}Code;
void read_Binary_File(FILE* binaryFile) {
	//FILE* binaryFile = fopen(binaryFilePath, "rb");
	char binChar;
	int mask = 1;
	for (int k = 0; k < 4 - 1; k++)
	{
		mask <<= 1;
		mask += 1;
	}
	printf("----------readBinaryFile-------\n");
	while (!feof(binaryFile)) {
		fread(&binChar, sizeof(char), 1, binaryFile);
		printf("%d\n", binChar & mask);
		//printf("%d\n", binChar);
	}
	fclose(binaryFile);
}
void unCombine(int codeChar, int* code1, int* code2)
{
	int mask = 0xF;
	//for (int k = 0; k < LENGTH_CODE / 3 - 1; k++)
	//{
	//	mask <<= 1;
	//	mask += 1;
	//}
	//takes the right(low) 4 bits.
	*code1 = codeChar & mask;
	codeChar >>= LENGTH_CODE / 3;
	//takes the small(high) 4 bits.
	*code2 = codeChar & mask;
}
//Building a counter array according to the frequency of the characters in the file.
void buildfrequencyArray(FILE* intermediateFile, int* counter)
{//

	char codeChar;
	int code1, code2;
	//codeChar = fgetc(intermediateFile);
	fread(&codeChar, sizeof(char), 1, intermediateFile);
	unCombine(codeChar, &code1, &code2);
	int convert;
	while (!feof(intermediateFile))
	{
		/*	if ((int)codeChar < '0')
				counter[codeChar]++;
			else
			{
				convert = (int)codeChar - '0';
				counter[convert]++;
			}*/
			//counter[codeChar]++;
		counter[code1]++;
		counter[code2]++;
		fread(&codeChar, sizeof(char), 1, intermediateFile);
		unCombine(codeChar, &code1, &code2);
	}
}
//Prints the elements of the array.
void printArray(int* arr)
{
	compressPrintFile = fopen("compressPrintFile.txt", "a+");
	if (!compressPrintFile)
	{
		printf("unable to open the compressPrintFile file.");
		exit(1);
	}
	for (int i = 0; i < SIZE; i++)
	{
		if (arr != NULL && arr[i] >= 0)
		{
			printf("%d ,", arr[i]);
			fprintf(compressPrintFile, "%d ", arr[i]);
		}
	}
	printf("\n");
	fprintf(compressPrintFile, "\n");
	fclose(compressPrintFile);
}
//Prints the elements of the matrix.
void printmat(Code** arr)
{
	for (int i = 0; i < SIZE; i++)
	{
		printArray(arr[i]->codeArray);
	}
	printf("\n");
	fprintf(compressPrintFile, "\n");
	fclose(compressPrintFile);
}
//Initialize the array.
void initArr(int* arr)
{
	for (int i = 0; i < SIZE; i++)
	{
		arr[i] = -1;
	}
}
//Initialize the matrix.
void initMat(Code** arr)
{
	for (int i = 0; i < SIZE; i++)
	{
		arr[i] = (Code*)malloc(sizeof(Code*));
		if (!arr[i])
		{
			printf("unable to allocate memory.");
			exit(1);
		}
		arr[i]->codeArray = NULL;
	}
}
//The main function to compress the file.
void compressHuffman(char* compressionPath, char* resultPath)
{
	FILE* intermediateFile, * decompressFile;
	int frequencyArray[SIZE] = { 0 };
	//open the files.
	//fopen_s(&compressHuffmanPrintFile, "compressHuffmanPrintFile.txt", "w");
	fopen_s(&intermediateFile, compressionPath, "rb");
	fopen_s(&decompressFile, "decompressFile.bin", "wb");
	char ch = '#';
	if (!decompressFile || !intermediateFile)
	{
		printf("unable to open the file.");
		exit(1);
	}
	/*401518
		475250
		413814
		405604
		491635
		417911
		401526
		417910
		405766
		393315*/
	buildfrequencyArray(intermediateFile, frequencyArray);
#ifdef PRINT_COMPRESS
	printArray(frequencyArray);
#endif // PRINT_COMPRESS
	const char const data[SIZE] = { '0','1','2','3','4','5','6','7','8','9' };
	//for (int i = 0; i < SIZE; i++)
	//{
	//	printf("%d\n", data[i] - '0');
	//}
	HuffmanCodes(data, intermediateFile, decompressFile, frequencyArray, SIZE);
	fclose(intermediateFile);
	fclose(decompressFile);
}
void readFile(FILE* binaryFile) {
	//FILE* binaryFile = fopen(binaryFilePath, "rb");
	char binChar;
	printf("----------readBinaryFile-------\n");
	while (!feof(binaryFile)) {
		fread(&binChar, sizeof(char), 1, binaryFile);
		printf("%d\n", binChar);
		//printf("%d\n", binChar);
	}
	fclose(binaryFile);
}
//Writing the contents of the tree into the file.
void writeTreeToDecompressFile(FILE* decompressFile, MinHeapNode* root)
{
	//01->left child
	//10->right child
	//11->leaf
	char str[] = "00";
	char* strToPrint = (char*)malloc(sizeof(char) * 3);
	if (!strToPrint)
	{
		printf("unable to allocate memory.");
		exit(1);
	}
	strToPrint[2] = '\0';
	if (!root->left && !root->right)
	{
		strcpy(str, "11");
		fwrite(str, sizeof(str)-1, 1, decompressFile);
		fwrite(&root->data, sizeof(char), 1, decompressFile);
		return;
	}
	if (root->left)
	{
		strcpy(str, "01");
		fwrite(str, sizeof(str)-1, 1, decompressFile);
		printf("%s: \n", strToPrint);
	}
	writeTreeToDecompressFile(decompressFile, root->left);
	if (root->right)
	{
		strcpy(str, "10");
		fwrite(str, sizeof(str)-1, 1, decompressFile);
	}
	writeTreeToDecompressFile(decompressFile, root->right);
}
// The main function that builds Huffman tree.
MinHeapNode* buildHuffmanTree(char data[], int freq[], int size)
{
	MinHeapNode* left, * right, * top;
	// Step 1: Create a min heap of capacity
	// equal to size. Initially, there are
	// modes equal to size.
	MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);
	// Iterate while size of heap doesn't become 1
	while (!isSizeOne(minHeap))
	{
		// Step 2: Extract the two minimum
		// freq items from min heap
		left = extractMin(minHeap);
		right = extractMin(minHeap);
		// Step 3: Create a new internal
		// node with frequency equal to the
		// sum of the two nodes frequencies.
		// Make the two extracted node as
		// left and right children of this new node.
		// Add this node to the min heap
		// '$' is a special value for internal nodes, not
		// used
		top = newNode('$', left->freq + right->freq);
		top->left = left;
		top->right = right;
		insertMinHeap(minHeap, top);
	}
	// Step 4: The remaining node is the
	// root node and the tree is complete.
	return extractMin(minHeap);
}
// write the huffman codes into matrix from the root of Huffman Tree.
// It uses arr[] to store codes.
void createCodes(Code** codeArrayOfAllChar, MinHeapNode* root, int codeArray[], int top,int count)
{
	// Assign 0 to left edge and recur
	if (root->left)
	{
		codeArray[top] = 0;
		count++;
		createCodes(codeArrayOfAllChar, root->left, codeArray, top + 1, count);
	}
	// Assign 1 to right edge and recur
	if (root->right)
	{
		codeArray[top] = 1;
		count++;
		createCodes(codeArrayOfAllChar, root->right, codeArray, top + 1, count);
	}
	// If this is a leaf node, then
	// it contains one of the input
	// characters,enter its code from arr[] into the matrix.
	if (isLeaf(root))
	{
		printf("%c: ", root->data);
		//The array at its character position is equal to its code.
		int* arr = (int*)malloc(SIZE * sizeof(int));
		if (!arr)
		{
			printf("unable to allocate memory.");
			exit(1);
		}
		initArr(arr);
		for (int i = 0; i < SIZE; i++)
		{
			if (codeArray[i] >= 0)
				arr[i] = codeArray[i];
		}
		codeArrayOfAllChar[root->data - '0']->codeArray = arr;
		codeArrayOfAllChar[root->data - '0']->count = count;
		count = 0;
#ifdef PRINT_COMPRESS
		compressPrintFile = fopen("compressPrintFile.txt", "a+");
		if (!compressPrintFile)
		{
			printf("unable to open the compressPrintFile file.");
			exit(1);
		}
		printf("arr:__________________\n");
		fprintf(compressPrintFile, "arr:__________________\n");
		printArray(arr);
		printf("%d : codeArrayOfAllChar[root->data - '0']:__________________\n", root->data - '0');
		fprintf(compressPrintFile, "%d : codeArrayOfAllChar[root->data - '0']:__________________\n", root->data - '0');
		printArray(codeArrayOfAllChar[root->data - '0']->codeArray);
		printf("codeArrayOfAllChar:__________________\n");
		fprintf(compressPrintFile, "codeArrayOfAllChar:__________________\n");
		printmat(codeArrayOfAllChar);
		fclose(compressPrintFile);
#endif // PRINT_COMPRESS
	}
}
int readCodesFromFile(FILE* intermediateFile, FILE* decompressFile, Code** codeArrayOfAllChar)
{
	int codeChar,currentCount=0,prevCount=0;
	int mask=0xF,res;
	long long codeCombine=0,code;
	res=fread(&codeChar, LENGTH_READ_CODE, 1, intermediateFile);
	if (res < 1)
		return res;
	printf("%x\n", codeChar);
	//fprintf(compressHuffmanPrintFile, "%x\n", codeChar);
	for (int i = 0; i < (LENGTH_READ_CODE*8)/ LENGTH_CODE_IN_BIT; i++)
	{
		code = codeArrayOfAllChar[codeChar & mask]->codeArray;
		currentCount = codeArrayOfAllChar[codeChar & mask]->count;
		prevCount += currentCount;
		if (prevCount % 8!=0)
		{
			codeCombine = combineTwoNumbers(code, codeCombine, currentCount);
			codeChar >>= LENGTH_CODE_IN_BIT;
			continue;
		}
		codeChar >>= LENGTH_CODE_IN_BIT;
		codeCombine = combineTwoNumbers(code, codeCombine, currentCount);
		fwrite(&codeCombine, prevCount/8, 1, decompressFile);
		prevCount = 0;
		//printArray(codeArrayOfAllChar[codeChar & mask]);
		printf("codeChar&mask= %x\n", codeChar & mask);
		//fprintf(compressHuffmanPrintFile, "codeChar&mask= %x\n",codeChar & mask);
	}
	return res;
}
//Writes the codes to the compressed.
void writeToDecompressFile(FILE* intermediateFile, FILE* decompressFile, int** codeArrayOfAllChar)
{
	int res = 1;
	//go through the file and each character read its code from the code array.
	fseek(intermediateFile, 0, SEEK_SET);
	//fwrite("$", sizeof(char), 1, decompressFile);
	while (res)
	{
		res=readCodesFromFile(intermediateFile, decompressFile,codeArrayOfAllChar);
	}
	//fclose(compressHuffmanPrintFile);
}
//The main function that builds a Huffman Treeand,
//write the codes into matrix by traversing
//the built Huffman Tree.
void HuffmanCodes(char* data, FILE* intermediateFile, FILE* decompressFile, int frequency[], int size)
{
	// Construct Huffman Tree
	MinHeapNode* root = buildHuffmanTree(data, frequency, size);
	//Writing the contents of the tree into the file.
	int sizeOfTree=0;
	fseek(decompressFile, 1, SEEK_SET);
	writeTreeToDecompressFile(decompressFile, root);
	//check the size of the tree.
	fseek(decompressFile, 0, SEEK_END);
	sizeOfTree = ftell(decompressFile);
	//write the size of the tree to the first byte in the file.
	fseek(decompressFile, 0, SEEK_SET);
	fwrite(&sizeOfTree, 1, 1, decompressFile);
	//return the mark to the end of the tree.
	fseek(decompressFile, sizeOfTree+2, SEEK_SET);
	//fwrite("$", sizeof(char), 1, decompressFile);
	//fseek(decompressFile, 0, SEEK_SET);
	//read_Binary_File(decompressFile);
	//readFile(decompressFile);
	
	// Write Huffman codes into matrix using
	// the Huffman tree built above
	int codeArray[SIZE], top = 0,count=0;
	//Saves all characters and their codes.
	//int** codeArrayOfAllChar = (int**)malloc(sizeof(int*) * SIZE);
	Code** codeArrayOfAllChar = (Code**)malloc(sizeof(Code*) * SIZE);
	if (!codeArrayOfAllChar)
	{
		printf("unable to allocate memory.");
		exit(1);
	}
	initMat(codeArrayOfAllChar);
	createCodes(codeArrayOfAllChar, root, codeArray, top,count);
	/*printf("codeArrayOfAllChar:__________________\n");
	printArray(codeArrayOfAllChar[0]);
	printmat(codeArrayOfAllChar);*/
	/*1, 1, 1, 1, 1,
		0, 1, 1,
		1, 0, 0,
		0, 0, 1,
		0, 0, 0,
		1, 0, 1, 0,
		1, 1, 0, 1, 1,
		1, 0, 1, 1,
		1, 1, 0, 0, 0,
		1, 1, 0, 0, 1,*/
	writeToDecompressFile(intermediateFile, decompressFile, codeArrayOfAllChar);
}
