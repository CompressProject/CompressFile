#include "LZW_Compress.h"
void readBinaryFile(char* binaryFilePath) {
	FILE* binaryFile = fopen(binaryFilePath, "rb");
	int binChar;
	int mask = 1;
	for (int k = 0; k < 24 - 1; k++)
	{
		mask <<= 1;
		mask += 1;
	}
	printf("----------readBinaryFile-------\n");
	while (!feof(binaryFile)) {
		fread(&binChar, 3 * sizeof(char), 1, binaryFile);
		printf("%d\n", binChar & mask);
	}
	fclose(binaryFile);
}
int combineTwoNumbers(codeChar, prevCodeChar)
{
	/*101= 110 0101
	101<<12 = 110 0101 0000 0000 0000
	 68 =100 0100
	res= 110 0101 0000 0100 0100*/
	codeChar <<= LENGTH_CODE;
	return codeChar | prevCodeChar;
}
void compressLZW(char* compressionPath, char* resultPath)
{
#pragma region variable assignments
	int codeChar, prevCodeChar, combineNum, count = 0;
	FILE* intermediateFile, * originalFile;
	char* currentString = (char*)malloc(2 * sizeof(char)), * newSequence;
	char nextCharacter = ' ', str[10];
#pragma endregion
#pragma region Initialization
	//init the 256 places in the table with their ascii code.
	CodeTable* codeTable = (CodeTable*)malloc(sizeof(CodeTable));
	init(codeTable);
	//open the files.
	fopen_s(&originalFile, compressionPath, "r");
	fopen_s(&intermediateFile, resultPath, "wb");
	if (!originalFile || !intermediateFile)
	{
		printf("unable to open the file.");
		exit(1);
	}
#pragma endregion
	currentString[0] = fgetc(originalFile);
	currentString[1] = NULL;
	nextCharacter = fgetc(originalFile);
	//go through the file to encoded it.
	while (nextCharacter != EOF)
	{
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
			//write the code in the binary file.
			if (count == 2)
			{
				combineNum = combineTwoNumbers(codeChar, prevCodeChar);
				fwrite(&combineNum, 3 * sizeof(char), 1, intermediateFile);
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
	fclose(intermediateFile);
	//readBinaryFile("C:\\γρι\\CompressFile\\CompressFile\\result.bin");
	//close the files.
	fclose(originalFile);
	fclose(intermediateFile);
}