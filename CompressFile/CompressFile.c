//#define _CRT_SECURE_NO_WARNINGS
//
//# include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//
//char* append(char*, char);
//
//int main()
//{
//    FILE* originalFile;
//    FILE* intermediateFile;
//    char currentChar;
//    printf("Opening the file test.txt in read mode\n");
//    originalFile = fopen("test.txt", "r"); // opening an existing file
//    if (originalFile == NULL)
//    {
//        printf("Could not open file test.txt\n");
//        return 1;
//    }
//    printf("Opening the file intermediateFile in read and write mode\n");
//    intermediateFile = fopen("intermediate.txt", "r");
//    if (intermediateFile == NULL) {
//        printf("Could not open file intermediate.txt\n");
//        return 1;
//    }
//    printf("\nReading the file test.txt and copy to intermediate.txt\n");
//    currentChar = fgetc(originalFile);
//    while (currentChar != EOF)
//    {
//        printf("%c", currentChar);
//        currentChar = fgetc(originalFile);
//        fputc(currentChar, intermediateFile);
//    }   
//    printf("\nReading the file intermediate.txt\n");
//    currentChar = fgetc(intermediateFile);
//    while (currentChar != EOF)
//    {
//        printf("%c", currentChar);
//        currentChar = fgetc(intermediateFile);
//    }
//    printf("\nClosing the file test.txt\n");
//    fclose(originalFile);
//    fclose(intermediateFile);// Closing the file
//    printf("_______________________________\n");
//    char* str = "b";
//    char c = 'H';
//    printf("%s\n", append(str, c));
//    printf("\n_______________________________\n");
//    return 0;
//}
//
//char* append(char* str, char c) {
//    size_t len = strlen(str);
//    char* str2 = malloc(len + 2);
//    strcpy(str2, str);
//    str2[len] = c;
//    str2[len + 1] = '\0';
//    return str2;
//}

#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include "LZW.h"
#define __STDC_WANT_LIB_EXT1__ 1
#define SIZE_TABLE 4096
#define MULTIPLIER 25


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

FILE* compressLZW(FILE*);



int main()
{
	/*HashTable* hash = (HashTable*)malloc(sizeof(HashTable));
	int res;
	init(hash);
	res = find(hash, "h");
	if (res == -1)
		insert(hash, "h");
	res = find(hash, "he");
	if (res == -1)
		insert(hash, "he");
	res = find(hash, "he");
	insert(hash, "hel");
	insert(hash, "hello");
	printf("after --------------------------------\n");
	for (int i = 0; i < SIZE_TABLE; i++)
	{
		if (hash->CodeTable[i])
		{
			printf("\n%s,", (hash->CodeTable[i]));
			printf("i= %d ", i);
		}
	}*/
	//compressLZW("C:\wd\file_to_compress.txt");
	decompressLZW("text.txt");
}
FILE* compressLZW(char* path)
{
	FILE* intermediateFile, * originalFile;
	char* currentString = "h", convert, temp;
	char nextCharacter = 'f';
	int nextAscii = 0;
	printf("%s\n", append(currentString, nextCharacter));
	//printf("%c", temp);
	//int code;
	//int counterArray[SIZE_TABLE];
	HashTable* codeTable = (HashTable*)malloc(sizeof(HashTable));
	init(codeTable);
	originalFile = fopen("file1.txt", "r");
	intermediateFile = fopen("intermediateFile.txt", "a+");
	if (!originalFile || !intermediateFile)
	{
		printf("unable to open the file.");
		exit(1);
	}
	currentString = fgetc(originalFile);
	nextCharacter = (char)currentString;
	printf("nextCharacter=%c\n", nextCharacter);
	while (nextCharacter != EOF)
	{
		/*nextAscii = fgetc(originalFile);
		nextCharacter =(char)nextAscii;*/
		nextCharacter = fgetc(originalFile);
		printf("nextCharacter=%c\n", nextCharacter);
		printf("currentString=%c\n", currentString);
		if (find(codeTable, append(currentString, nextCharacter)) != -1)
		{
			currentString += nextCharacter;
		}
		else
		{
			convert = convertIntToChar(hashCode(currentString));
			fputs(convert, intermediateFile);
			insert(codeTable, currentString + nextCharacter);
			currentString = nextCharacter;
		}
	}
	fclose(originalFile);
	fclose(intermediateFile);
	return intermediateFile;
}