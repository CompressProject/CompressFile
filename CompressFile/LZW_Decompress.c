#define _CRT_SECURE_NO_WARNINGS
#include "LZW_Decompress.h"
//the main function to compress the file.
void decompressLZW(char* decompressionPath, char* resultPath) {
#pragma region Initializing 
	//Opening files.
	FILE* decompressFile, * originalDataFile;
	decompressPrintFile = fopen("decompressPrintFile.txt", "w");
	decompressFile = fopen(decompressionPath, "rb");
	originalDataFile = fopen(resultPath, "w");
	if (!originalDataFile || !decompressFile || !decompressPrintFile)
	{
		printf("unable to open the file.");
		exit(1);
	}
	//Initializing variables and data structures.
	CodeTable* codeTable = (CodeTable*)malloc(sizeof(CodeTable));
	init(codeTable);
	int currentCode = 0, res = 1, code1 = 0, code2 = 0, size, oldCode = 0;
	char* translation = NULL;
	char* previousTranslation = "?";
	char firstPreviousChar = '?';
	char* temp;
	bool flag = 0;//keep if to read the next pair.
	//check if the file is empty.
	fseek(decompressFile, 0, SEEK_END);
	size = ftell(decompressFile);
	if (size == 0)
	{
		printf("the file is empty.");
		fclose(decompressFile);
		fclose(originalDataFile);
		fclose(decompressPrintFile);
		return;
	}
	fseek(decompressFile, 0, SEEK_SET);
#pragma endregion
#pragma region special attention for the first char
	//read the next pair code.
	readCharactersFromFile(decompressFile, &code1, &code2);
	currentCode = code1;
	//check if the code is correct.
	currentCode = checkCodeValidation(currentCode);
	if (currentCode >= 0)
	{
		translation = codeTable->CodeArray[currentCode];
		fputs(translation, originalDataFile);
		firstPreviousChar = translation[0];
		previousTranslation = translation;
	}
#pragma endregion
	while (res)
	{
		//read the next pair code.
		if (flag)
		{
			res = readCharactersFromFile(decompressFile, &code1, &code2);
			if (res < 1)
				continue;
#ifdef PRINT_DECOMPRESS
			printf("read from file code1:%d\n", code1);
			printf("read from file code2:%d\n", code2);
			fprintf(decompressPrintFile, "read from file code1:%d\n", code1);
			fprintf(decompressPrintFile, "read from file code2:%d\n", code2);
#endif // PRINT_DECOMPRESS
			currentCode = code1;
		}
		else
		{
			if (code2 == SIGN)
			{
				flag = !flag;
				continue;
			}
			currentCode = code2;
		}
		flag = !flag;
		//check if the code is correct.
		currentCode = checkCodeValidation(currentCode);
		if (currentCode < 0)
			continue;
		//translate the code.
		translation = codeTable->CodeArray[currentCode];
		if (translation == NULL)
		{
			translation = append(previousTranslation, firstPreviousChar);
		}
		//write the code translation to the file.
#ifdef PRINT_DECOMPRESS
		puts(translation);
		fprintf(decompressPrintFile, "translation: %s\n", translation);
#endif // PRINT_DECOMPRESS
		fputs(translation, originalDataFile);
		//update variables and insert new value to the hash table.
		firstPreviousChar = translation[0];
		temp = _strdup(append(previousTranslation, firstPreviousChar));
		if (find(codeTable, temp) == -1)
			insert(codeTable, temp);
		previousTranslation = _strdup(translation);
	}
	fclose(decompressPrintFile);
	printTable(codeTable);
	fclose(decompressPrintFile);
	read(decompressionPath);
	//close the files.
	fclose(decompressPrintFile);
	fclose(decompressFile);
	fclose(originalDataFile);
	fclose(compressPrintFile);
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
int readCharactersFromFile(FILE* decompressFile, int* code1, int* code2)
{
	int code, res;
	res = fread(&code, LENGTH_READ_CODE, 1, decompressFile);
	unCombineTwoNumbers(code, code1, code2);
	return res;
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
void read(char* binaryFilePath)
{
	FILE* binaryFile = fopen(binaryFilePath, "rb");
	fopen_s(&decompressPrintFile, "decompressPrintFile.txt", "a+");
	if (!decompressPrintFile)
	{
		printf("unable to open the decompressPrintFile file.");
		exit(1);
	}
	int binChar;
	int mask = 1;
	for (int k = 0; k < 24 - 1; k++)
	{
		mask <<= 1;
		mask += 1;
	}
#ifdef PRINT_DECOMPRESS
	printf("----------decompress-------\n");
	fprintf(decompressPrintFile, "----------decompress-------\n");
	while (!feof(binaryFile))
	{
		fread(&binChar, sizeof(int), 1, binaryFile);
		printf("%d\n", binChar & mask);
		fprintf(decompressPrintFile, "%d\n", binChar & mask);
		//printf("%d\n", binChar);
	}
#endif // PRINT_DECOMPRESS
	fclose(binaryFile);
}