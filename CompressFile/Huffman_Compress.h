#pragma once
#pragma once
#include "DataStructuresHuffman.h";
//#include "CommonFunction.h"
#define SIZE 10
void buildfrequencyArray(FILE* intermediateFile, int* counter);
void createCodes(int** codeArrayOfAllChar, MinHeapNode* root, int codeArray[], int top);
void writeToCodeArray(int** codeArrayOfAllChar, int codeArray[], int n);
void HuffmanCodes(char* data, FILE* intermediateFile, FILE* decompressFile, int frequency[], int size);
MinHeapNode* buildHuffmanTree(char data[], int freq[], int size);
void writeToDecompressFile(FILE* intermediateFile, FILE* decompressFile, int** codeArrayOfAllChar);
void compressHuffman(char*, char*);
void writeTreeToDecompressFile(FILE* decompressFile, MinHeapNode* root);
int readCodesFromFile(FILE* intermediateFile, FILE* decompressFile, int** codeArrayOfAllChar);

