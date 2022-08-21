#pragma once
#include "CommonFunction.h"
//represent the code table.
typedef struct CodeTable
{
	int size;
	char* CodeArray[SIZE_TABLE];
}CodeTable;
//Initialize the first 256 places according to their ASCII code.
void init(CodeTable*);
//insert new sequence to the hash table.
void insert(CodeTable*, char*);
//Searches if the sequence exists in the table.
int find(CodeTable*, char*);
//print the table.
void printTable(CodeTable* );

