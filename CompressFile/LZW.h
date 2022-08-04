#ifndef _LZW_H
#define _LZW_H
#include "Common_Functions.h"
typedef struct HashTable
{
	int size;
	char* CodeTable[SIZE_TABLE];
}HashTable;
void init(HashTable* hashTable);
int hashCode(char* value);
void insert(HashTable* hashTable, char* value);
int find(HashTable* hashTable, char* value);
void print(HashTable* hashTable);

#endif // !_LZW_H
