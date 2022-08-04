#include "LZW.h"

//Utility for generating Hoffmann code.
typedef struct TreeNode {
	char data;
	struct TreeNode* left;
	struct TreeNode* right;
}TreeNode;
//represent the chars and their frequency.
typedef struct NodeHeap {
	int frequency;
	struct NodeHeap* left;
	struct NodeHeap* right;
	struct TreeNode* tree;
}NodeHeap;

void printBits(int);

int main()
{
	decompressLZW("text.txt");
#pragma region "learn binary file"
	//FILE* fp = fopen("newBinary.bin", "wb");
	//if (fp == NULL) {
	//	printf("error creating file");
	//	return -1;
	//}
	//char char1 = '0',c = '0';
	//char* string = "000";
	//for (int i = 0; i < 32; i++) {
	//	char1 = i%2;
	//	fwrite(&char1, 1, 1, fp);
	//}
	//fwrite('\n', 1, 1, fp);
	//for (int i = 0; i < 32; i++) {
	//	string = "110";
	//	fwrite(&char1, 1, 1, fp);
	//}
	//fclose(fp);
	//fp = fopen("newBinary.bin", "rb");
	//for (int i = 0; i < 64; i++) {
	//	fread(&c, sizeof(char), 1, fp);
	//	printf("%d", c);
	//}
	//fclose(fp);
#pragma endregion

	/*FILE* fp = fopen("newBinary2.bin", "wb");
	if (fp == NULL) {
		printf("error creating file");
		return -1;
	}
	int val = 197;
	int res = 0;
	char* char_code = "97";
	fwrite(&val, sizeof(int), 1, fp);
	fclose(fp);
	fp = fopen("newBinary2.bin", "rb");
	fread(&res, sizeof(int), 1, fp);
	printf("%d ", res);
	fclose(fp);
	return 0;*/
}

void printBits(int num)
{
	for (int i = 0; i < sizeof(int) * 8; i++)
	{
		printf("%d", (num >> sizeof(int) * 8 - 1) & 1);
		num <<= 1;
	}
	printf("\n");
}