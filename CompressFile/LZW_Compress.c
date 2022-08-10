#include "LZW_Compress.h"
void convertIntToBinary(FILE* binFile, int number) {
	//FILE* binFile = fopen(binaryFilePath, "wb");
	//int binary;
	bool binary;
	int mask = 1;
	mask <<= LENGTH_CODE;
	for (int i = 0; i < 12; i++) {
		mask >>= 1;
		//binary = (number & mask) ? 1 : 0;
		binary = number & mask;
		fwrite(&binary, 1, 1, binFile);
		printf("%i", binary);
	}
	printf("\n");
	//fclose(binFile);
}
void readBinaryFile(char* binaryFilePath) {
	FILE* binaryFile = fopen(binaryFilePath, "rb");
	char binChar;
	while (!feof(binaryFile)) {
		fread(&binChar, 1, 1, binaryFile);
		printf("%d", binChar);
	}
	fclose(binaryFile);
}
int combineTwoNumbers(codeChar, prevCodeChar)
{
	//101= 110 0101
	//101<<12 = 110 0101 0000 0000 0000
	// 68 =100 0100
	//res= 110 0101 0000 0100 0100
	//int combineNum= prevCodeChar;
	codeChar <<= LENGTH_CODE;
	return codeChar | prevCodeChar;
}

//compress the file using the lzw method.
void compressLZW(char* compressionPath, char* resultPath)
{
	int res = 0, count = 0;
	int codeChar,prevCodeChar, lenTemp, combineNum;
	FILE* intermediateFile, * originalFile;
	char* currentString = (char*)malloc(2 * sizeof(char)), * convert, * newSequence;
	char nextCharacter = ' ', str[10];
#pragma region Initialization
	//init the 256 places in the table with their ascii code.
	HashTable* codeTable = (HashTable*)malloc(sizeof(HashTable));
	init(codeTable);
	//open the files.
	fopen_s(&originalFile, compressionPath, "r");
	fopen_s(&intermediateFile, "result.bin", "wb");
	//fopen_s(&intermediateFile, "result.txt", "w");
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
		//printf("nextCharacter= %c\n", nextCharacter);
		//printf("currentString= ");
		//puts(currentString);
		newSequence = append(currentString, nextCharacter);
		//puts(newSequence);
		//search if the new sequence is in the table.
		if (find(codeTable, newSequence) != -1)
		{
			currentString = newSequence;
		}
		else
		{
			count++;
			//printf("hashCode(currentString)= %d\n", hashCode(currentString));
			//find hashcode of the currentString.
			codeChar = find(codeTable, currentString);
			//convert = convertIntToChar(tempHash);
			//lenTemp = strlen(convert);
			////generate any code in 4 digits.
			//lenTemp = 4 - lenTemp;
			//while (lenTemp < 4 && lenTemp != 0)
			//{
			//	convert = appendFromBegin(convert, '0');
			//	lenTemp--;
			//}
			//write the code in the file.
			 //write to binary file
			//convertIntToBinary(intermediateFile, tempHash);
			if (count == 2)
			{//110 0101 0000 0100 0100
			// res=110 0100 1001 1100 01
				combineNum=combineTwoNumbers(codeChar,prevCodeChar);
				printf("%d\n", combineNum);
				fwrite(&combineNum, 3 * sizeof(char), 1, intermediateFile);
				count = 0;
			}
			int temp;
			/*fseek(intermediateFile, -1, SEEK_CUR);
			fread(&temp, 3 * sizeof(char), 1, intermediateFile);
			printf("read: %d\n", temp);*/
			//fseek(intermediateFile,1, SEEK_CUR);
			prevCodeChar = codeChar;
			printf("0x%x\n", codeChar);
			// write to text file.
			//fputs(convert, intermediateFile);
			//insert the new sequence into the table.
			insert(codeTable, newSequence);
			str[0] = nextCharacter;
			currentString = _strdup(str);
			*(currentString + 1) = '\0';
			//puts(currentString);
		}
		nextCharacter = fgetc(originalFile);
		//puts(currentString);
	}
	//readBinaryFile("C:\\γρι\\CompressFile\\CompressFile\\result.bin");
	print(codeTable);
	//close the files.
	fclose(originalFile);
	fclose(intermediateFile);
}

