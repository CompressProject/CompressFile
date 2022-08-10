#include "Huffman_Compress.h"
//Building a counter array according to the frequency of the characters in the file.
void buildfrequencyArray(FILE* intermediateFile, int* counter)
{
	char codeChar;
	codeChar = fgetc(intermediateFile);
	int convert;
	while (codeChar != EOF)
	{
		convert = (int)codeChar - '0';
		counter[convert]++;
		codeChar = fgetc(intermediateFile);
	}
}
//Prints the elements of the array.
void printArray(int* arr)
{
	for (int i = 0; i < SIZE; i++)
	{
		if (arr != NULL && arr[i] >= 0)
			printf("%d ,", arr[i]);
	}
	printf("\n");
}
//Prints the elements of the matrix.
void printmat(int** arr)
{
	for (int i = 0; i < SIZE; i++)
	{
		printArray(arr[i]);
	}
	printf("\n");
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
void initMat(int** arr)
{
	for (int i = 0; i < SIZE; i++)
	{
		arr[i] = NULL;
	}
}
//The main function to compress the file.
void compressHuffman(char* compressionPath, char* resultPath)
{
	FILE* intermediateFile, * decompressFile;
	int frequencyArray[SIZE] = { 0 };
	char data[SIZE] = { '0','1','2','3','4','5','6','7','8','9' };
	//open the files.
	fopen_s(&intermediateFile, compressionPath, "r");
	fopen_s(&decompressFile, "originalData.bin", "wb");
	char ch = '#';
	if (!decompressFile || !intermediateFile)
	{
		printf("unable to open the file.");
		exit(1);
	}
	buildfrequencyArray(intermediateFile, frequencyArray);
	printArray(frequencyArray);
	HuffmanCodes(data, intermediateFile, decompressFile, frequencyArray, SIZE);
	fclose(intermediateFile);
	fclose(decompressFile);
}
//Writing the contents of the tree into the file.
void writeTreeToDecompressFile(FILE* decompressFile, MinHeapNode* root)
{
	//char str[2]="";
	if (!root)
	{
		fwrite("@", sizeof(char), 1, decompressFile);
		return;
	}
	if (root->data != '$') {
		fwrite(&root->data, sizeof(char), 1, decompressFile);
		//fread(str, 1, 1, decompressFile);
	}
	writeTreeToDecompressFile(decompressFile, root->left);
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
void createCodes(int** codeArrayOfAllChar, MinHeapNode* root, int codeArray[], int top)
{
	// Assign 0 to left edge and recur
	if (root->left)
	{
		codeArray[top] = 0;
		createCodes(codeArrayOfAllChar, root->left, codeArray, top + 1);
	}
	// Assign 1 to right edge and recur
	if (root->right)
	{
		codeArray[top] = 1;
		createCodes(codeArrayOfAllChar, root->right, codeArray, top + 1);
	}
	// If this is a leaf node, then
	// it contains one of the input
	// characters,enter its code from arr[] into the matrix.
	if (isLeaf(root))
	{
		printf("%c: ", root->data);
		//The array at its character position is equal to its code.
		int* arr = (int*)malloc(SIZE * sizeof(int));
		initArr(arr);
		for (int i = 0; i < SIZE; i++)
		{
			if (codeArray[i] >= 0)
				arr[i] = codeArray[i];
		}
		codeArrayOfAllChar[root->data - '0'] = arr;
		/*printf("arr:__________________\n");
		printArray(arr);
		printf("%d : codeArrayOfAllChar[root->data - '0']:__________________\n", root->data - '0');
		printArray(codeArrayOfAllChar[root->data - '0']);
		printf("codeArrayOfAllChar:__________________\n");
		printmat(codeArrayOfAllChar);*/
	}
}
//Writes the codes to the compressed.
void writeToDecompressFile(FILE* intermediateFile, FILE* decompressFile, int** codeArrayOfAllChar)
{
	//go through the file and each character read its code from the code array.
	char ch;
	char* temp = "";
	fseek(intermediateFile, 0, SEEK_SET);
	fwrite("$", sizeof(char), 1, decompressFile);
	while ((ch = fgetc(intermediateFile)) != EOF)
	{
		/*printf("ch= %c\n", ch);
		printArray(codeArrayOfAllChar[ch - '0']);*/
		fwrite(codeArrayOfAllChar[ch - '0'], 1, sizeof(codeArrayOfAllChar[ch - '0']) / sizeof(int), decompressFile);
		//fread(temp, 1, sizeof(codeArrayOfAllChar[ch - '0']), decompressFile);
	}
}
//The main function that builds a Huffman Treeand,
//write the codes into matrix by traversing
//the built Huffman Tree.
void HuffmanCodes(char* data, FILE* intermediateFile, FILE* decompressFile, int frequency[], int size)
{
	// Construct Huffman Tree
	MinHeapNode* root = buildHuffmanTree(data, frequency, size);
	//Writing the contents of the tree into the file.
	writeTreeToDecompressFile(decompressFile,root);
	char str[3];
	/*fseek(decompressFile, 0, SEEK_SET);
	fclose(decompressFile);
	fopen_s(&decompressFile, "originalData.bin", "rb");
	while (!feof(decompressFile))
	{
		fread(str, 1, 1, decompressFile);
		printf("______________str___________");
		puts(str);
	}*/
	// Write Huffman codes into matrix using
	// the Huffman tree built above
	int codeArray[SIZE], top = 0;
	//Saves all characters and their codes.
	int** codeArrayOfAllChar = (int**)malloc(sizeof(int*) * SIZE);
	initMat(codeArrayOfAllChar);
	createCodes(codeArrayOfAllChar, root, codeArray, top);
	/*printf("codeArrayOfAllChar:__________________\n");
	printArray(codeArrayOfAllChar[0]);
	printmat(codeArrayOfAllChar);*/
	writeToDecompressFile(intermediateFile, decompressFile, codeArrayOfAllChar);
}
