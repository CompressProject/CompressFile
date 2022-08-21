#define _CRT_SECURE_NO_WARNINGS
#include "decompress_LZW.h"
//the main function to compress the file.
void decompressLZW(char* decompressionPath, char* resultPath) {
#pragma region Initializing 
	//Opening files.
	FILE* decompressFile, * originalDataFile;
	decompressFile = fopen(decompressionPath, "rb");
	originalDataFile = fopen(resultPath, "w");
	if (!originalDataFile || !decompressFile)
	{
		printf("unable to open the file.");
		exit(1);
	}
	//Initializing variables and data structures.
	CodeTable* codeTable = (CodeTable*)malloc(sizeof(CodeTable));
	init(codeTable);
	int currentCode = 0, code1 = 0, code2 = 0;
	char* translation = NULL;
	char* previousTranslation = "?";
	char firstPreviousChar = '?';
	char* temp;
	bool flag = 0;//keep if to read the next pair.
#pragma endregion
#pragma region special attention for the first char
	//read the next pair code.
	readCharactersFromFile(decompressFile, &code1, &code2);
	currentCode = code1;
	//check if the code is correct.
	currentCode = checkCodeValidation(currentCode);
	if (currentCode >= 0) {
		translation = codeTable->CodeArray[currentCode];
		fputs(translation, originalDataFile);
		printf("%s\n", translation);
		firstPreviousChar = translation[0];
		previousTranslation = translation;
	}
#pragma endregion
	while (!feof(decompressFile))
	{
		//read the next pair code.
		if (flag)
		{
			readCharactersFromFile(decompressFile, &code1, &code2);
			currentCode = code1;
		}
		else
			currentCode = code2;
		flag = !flag;
		//check if the code is correct.
		currentCode = checkCodeValidation(currentCode);
		if (currentCode < 0)
			continue;
		//translate the code.
		translation = codeTable->CodeArray[currentCode];
		if (translation == NULL)
			translation = append(previousTranslation, firstPreviousChar);
		//write the code translation to the file.
		fputs(translation, originalDataFile);
		//update variables and insert new value to the hash table.
		firstPreviousChar = translation[0];
		temp = _strdup(append(previousTranslation, firstPreviousChar));
		if (find(codeTable, temp) == -1)
			insert(codeTable, temp);
		previousTranslation = _strdup(translation);
	}
	//close the files.
	fclose(decompressFile);
	fclose(originalDataFile);
}
void unCombineTwoNumbers(int codeChar, int* code1, int* code2)
{
	int mask = 1;
	for (int k = 0; k < LENGTH_CODE - 1; k++)
	{
		mask <<= 1;
		mask += 1;
	}
	//takes the right(low) 12 bits.
	*code1 = codeChar & mask;
	codeChar >>= LENGTH_CODE;
	//takes the small(high) 12 bits.
	*code2 = codeChar & mask;
}
void readCharactersFromFile(FILE* decompressFile, int* code1, int* code2)
{
	int code;
	fread(&code, 3 * sizeof(char), 1, decompressFile);
	unCombineTwoNumbers(code, code1, code2);
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