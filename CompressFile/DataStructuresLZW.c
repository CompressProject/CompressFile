#include "DataStructuresLZW.h"
void init(CodeTable* CodeTable)
{
	CodeTable->size = 256;
	for (int i = 0; i < 256; i++)
	{
		char str[10] = { (char)i, '\0' };
		CodeTable->CodeArray[i] = _strdup(str);
	}
	for (int i = 256; i < SIZE_TABLE; i++)
	{
		CodeTable->CodeArray[i] = NULL;
	}
}
void insert(CodeTable* CodeTable, char* value) {
	if (CodeTable->size == SIZE_TABLE)
		return;
	CodeTable->CodeArray[CodeTable->size] = value;
	CodeTable->size++;
}
int find(CodeTable* CodeTable, char* value) {
	//if value is a single char
	if (value[1] == '\0')
		return value[0];
	//if value is a string
	for (int i = 0; i < CodeTable->size; i++) {
		if (strcmp(CodeTable->CodeArray[i], value) == 0)
			return i;
	}
	return -1;
}
void printTable(CodeTable* CodeTable) {
#ifdef PRINT_DECOMPRESS
	fopen_s(&decompressPrintFile, "decompressPrintFile.txt", "a+");
	if (!decompressPrintFile)
	{
		printf("unable to open the decompressPrintFile file.");
		exit(1);
	}
	printf("--------------------------------\n");
	fprintf(decompressPrintFile, "--------------------------------\n");
	for (int i = 0; i < SIZE_TABLE; i++) {
		printf("%4d  %8s\n", i, CodeTable->CodeArray[i]);
		fprintf(decompressPrintFile, "%4d  %8s\n", i, CodeTable->CodeArray[i]);
	}
	printf("--------------------------------\n");
	fprintf(decompressPrintFile, "--------------------------------\n");
#endif // PRINT_DECOMPRESS
#ifdef PRINT_COMPRESS 
	fopen_s(&compressPrintFile, "compressPrintFile.txt", "a+");
	if (!compressPrintFile)
	{
		printf("unable to open the compressPrintFile file.");
		exit(1);
	}
	printf("--------------------------------\n");
	fprintf(compressPrintFile,"--------------------------------\n");
	for (int i = 0; i < SIZE_TABLE; i++) {
		printf("%4d  %8s\n", i, CodeTable->CodeArray[i]);
		fprintf(compressPrintFile,"%4d  %8s\n", i, CodeTable->CodeArray[i]);
	}
	printf("--------------------------------\n");
	fprintf(compressPrintFile, "--------------------------------\n");
#endif // PRINT_COMPRESS
}
