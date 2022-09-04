#include "LZW_Compress.h"
void readBinaryFile(char* binaryFilePath) {
	FILE* binaryFile = fopen(binaryFilePath, "rb");
	//fopen_s(&compressPrintFile, "compressPrintFile.txt", "a+");
	int binChar;
	int mask = 1;
	for (int k = 0; k < 24 - 1; k++)
	{
		mask <<= 1;
		mask += 1;
	}
#ifdef PRINT_COMPRESS
	printf("----------readBinaryFile-------\n");
	fprintf(compressPrintFile, "readBinaryFile\n");
	while (!feof(binaryFile))
	{
		fread(&binChar, sizeof(int), 1, binaryFile);
		printf("%d\n", binChar & mask);
		fprintf(compressPrintFile, "%d\n", binChar & mask);
	}
#endif // PRINT_COMPRESS
	fclose(binaryFile);
}
void compressLZW(char* compressionPath, char* resultPath)
{
#pragma region variable assignments
	int codeChar = 0, prevCodeChar = 0, combineNum, count = 0, size;
	FILE* intermediateFile, * originalFile;
	char* currentString = (char*)malloc(2 * sizeof(char)), * newSequence;
	char nextCharacter = ' ', str[10];
	bool finished = false;
#pragma endregion
#pragma region Initialization
	//init the 256 places in the table with their ascii code.
	CodeTable* codeTable = (CodeTable*)malloc(sizeof(CodeTable));
	init(codeTable);
	//open the files.
	fopen_s(&compressPrintFile, "compressPrintFile.txt", "w");
	fopen_s(&originalFile, compressionPath, "r");
	fopen_s(&intermediateFile, resultPath, "wb");
	if (!originalFile || !intermediateFile || !compressPrintFile)
	{
		printf("unable to open the file.");
		exit(1);
	}
	//check if the file is empty.
	fseek(originalFile, 0, SEEK_END);
	size = ftell(originalFile);
	if (size == 0)
	{
		printf("the file is empty.\n");
		fclose(originalFile);
		fclose(intermediateFile);
		fclose(compressPrintFile);
		return;
	}
	fseek(originalFile, 0, SEEK_SET);
#pragma endregion
	currentString[0] = fgetc(originalFile);
	currentString[1] = NULL;
	nextCharacter = fgetc(originalFile);
	//go through the file to encoded it.
	while (!finished)
	{
		if (nextCharacter == EOF)
			finished = true;
		newSequence = append(currentString, nextCharacter);
		//search if the new sequence is in the table.
		if (find(codeTable, newSequence) != -1)
		{
			currentString = newSequence;
		}
		else
		{
			count++;
			//find hashcode of the currentString.
			codeChar = find(codeTable, currentString);
#ifdef PRINT_COMPRESS
			printf("codeChar= %d\n", codeChar);
			printf("prevCodeChar= %d\n", prevCodeChar);
			fprintf(compressPrintFile, "codeChar= %d\n", codeChar);
			fprintf(compressPrintFile, "prevCodeChar= %d\n", prevCodeChar);
#endif // PRINT_COMPRESS

			//write the code in the binary file.
			if (count == 2)
			{
				combineNum = combineTwoNumbers(codeChar, prevCodeChar,LENGTH_CODE);
#ifdef PRINT_COMPRESS
				printf("combineNum= %d\n", combineNum);
				fprintf(compressPrintFile, "combineNum= %d\n", combineNum);
#endif // PRINT_COMPRESS
				fwrite(&combineNum, LENGTH_READ_CODE, 1, intermediateFile);
				count = 0;
			}
			prevCodeChar = codeChar;
			//insert the new sequence into the table.
			insert(codeTable, newSequence);
			str[0] = nextCharacter;
			currentString = _strdup(str);
			*(currentString + 1) = '\0';
		}
		nextCharacter = fgetc(originalFile);
	}
	if (count == 1)
	{
		combineNum= combineTwoNumbers(SIGN, codeChar,LENGTH_CODE);
		fwrite(&combineNum, LENGTH_READ_CODE, 1, intermediateFile);
	}
#ifdef PRINT_COMPRESS
	printf("after while-codeChar= %d\n", codeChar);
	printf("after while-prevCodeChar= %d\n", prevCodeChar);
	fprintf(compressPrintFile, "after while-codeChar= %d\n", codeChar);
	fprintf(compressPrintFile, "after while-prevCodeChar= %d\n", prevCodeChar);
#endif // PRINT_COMPRESS
	fclose(intermediateFile);
	fclose(compressPrintFile);
	printTable(codeTable);
	readBinaryFile(resultPath);
	//close the files.
	fclose(compressPrintFile);
	fclose(originalFile);
	fclose(intermediateFile);
	fclose(decompressPrintFile);
}
