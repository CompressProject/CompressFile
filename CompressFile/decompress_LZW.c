#define _CRT_SECURE_NO_WARNINGS
#include "decompress_LZW.h"

void decompressLZW(char* path) {
#pragma region Initializing 
	//Opening files
	FILE* decompressFile, * originalDataFile;
	//decompressFile = fopen("decompressFile.txt", "r");
	decompressFile = fopen("result.bin", "rb");
	originalDataFile = fopen("originalData.txt", "w");
	if (!decompressFile) {
		printf("unable to open the decompressFile.");
		exit(1);
	}
	if (!originalDataFile) {
		printf("unable to open the originalDataFile.");
		exit(1);
	}
	//Initializing variables and data structures
	HashTable* codeTable = (HashTable*)malloc(sizeof(HashTable));
	init(codeTable);
	int currentCode = 0;
	char* translation  = NULL;
	char* previousTranslation = "?";
	char firstPreviousChar = '?';
	char* temp;
#pragma endregion
#pragma region "special attention for the first char"
	//read the next code
	currentCode = readFourCharactersFromFile(decompressFile);
	//check if the code is correct
	currentCode = checkCodeValidation(currentCode);
	if (currentCode >= 0) {
		translation = codeTable->CodeTable[currentCode];
		fputs(translation, originalDataFile);
		printf("%s\n", translation);
		firstPreviousChar = translation[0];
		previousTranslation = translation;
	}
#pragma endregion
#pragma region LZW
	while (!feof(decompressFile)) {
		//read the next code
		currentCode = readFourCharactersFromFile(decompressFile);
		//check if the code is correct
		currentCode = checkCodeValidation(currentCode);
		if (currentCode < 0)
			continue;
		//translate the code
		translation = codeTable->CodeTable[currentCode];
		if (translation == NULL)
			translation = append(previousTranslation, firstPreviousChar);
		//write the code translation to the file
		fputs(translation, originalDataFile);
		printf("%s\n", translation);
		//update variables and insert new value to the hash table
		firstPreviousChar = translation[0];
		temp = _strdup(append(previousTranslation, firstPreviousChar));
		if(find(codeTable,temp) == -1)
			insert(codeTable, temp);
		previousTranslation = _strdup(translation);
		//printf("%4d     %s\n", currentCode, translation);
	}
	fputs("\n------------------------\n", originalDataFile);
	print(codeTable);
	fclose(decompressFile);
	fclose(originalDataFile);
	return;
#pragma endregion
}
//int readFourCharactersFromFile(FILE* decompressFile) {
//	char currentFourChars[5];
//	char nextChar;
//	for (int i = 0; i < 4; i++) {
//		nextChar = fgetc(decompressFile);
//		if (nextChar == EOF) {
//			if (i == 0) {
//				return -1;
//			}
//			currentFourChars[i] = '\0';
//			return strtol(currentFourChars, NULL, 10) + SIZE_TABLE * 10;
//		}
//		currentFourChars[i] = nextChar;
//	}
//	currentFourChars[4] = '\0';
//	return strtol(currentFourChars, NULL, 10);
//}
int readFourCharactersFromFile(FILE* decompressFile) {
	int code;
	fread(&code, sizeof(int), 1, decompressFile);
	return code;
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