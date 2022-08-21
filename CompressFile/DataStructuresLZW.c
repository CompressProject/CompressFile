#include "DataStructuresLZW.h"
void init(CodeTable* CodeTable)
{
	CodeTable->size = 256;
	for (int i = 0; i < 256; i++)
	{
		char str[10] = { (char)i, "\0" };
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
	printf("\n\n--------------------------------\n");
	for (int i = 0; i < SIZE_TABLE; i++) {
		printf("%4x  %8s\n", i, CodeTable->CodeArray[i]);
	}
	printf("\n--------------------------------\n");
}
