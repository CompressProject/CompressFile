#define _CRT_SECURE_NO_WARNINGS
#include "decompress_LZW.h"


void decompressLZW(char* path) {
#pragma region Initializing 
	//Initializing variables and data structures and opening files
	FILE* decompressFile, * originalDataFile;
	decompressFile = fopen("decompressFile.txt", "a+");
	originalDataFile = fopen("originalData.txt", "a+");
	if (!decompressFile) {
		printf("unable to open the decompressFile.");
		exit(1);
	}
	if (!originalDataFile) {
		printf("unable to open the originalDataFile.");
		exit(1);
	}
	HashTable* codeTable = (HashTable*)malloc(sizeof(HashTable));
	init(codeTable);
#pragma endregion
	int x = 0;
	while (x > -1) {
		x = readFourCharactersFromFile(decompressFile);
		x = checkCodeValidation(x);
		printf("%d, ", x);
	}
	return;
}
int readFourCharactersFromFile(FILE* decompressFile) {
	char currentFourChars[5];
	char nextChar = 'f';
	for (int i = 0; i < 4; i++) {
		nextChar = fgetc(decompressFile);
		if (nextChar == EOF) {
			if (i == 0) {
				return -1;
			}
			currentFourChars[i] = '\0';
			return strtol(currentFourChars, NULL, 10) + SIZE_TABLE * 10;
		}
		currentFourChars[i] = nextChar;
	}
	currentFourChars[4] = '\0';
	return strtol(currentFourChars, NULL, 10);
}
int checkCodeValidation(int code) {
	if (code == -1) {
		printf("\nThe file has been read completly\n");
		return -1;
	}
	if (code >= SIZE_TABLE * 10) {
		printf("\nThe file may have gone wrong\n");
		return code - SIZE_TABLE * 10;
	}
	if (code > SIZE_TABLE || code < 0) {
		printf("\nsevere exception!\nExceeding hash table limits!\nThe file went wrong!\n");
		return -2;
	}
	return code;
}