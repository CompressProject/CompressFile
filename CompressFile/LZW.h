#ifndef _LZW_H
#define _LZW_H
#include "Common_Functions.h"
#define __STDC_WANT_LIB_EXT1__ 1
#define SIZE_TABLE 4096
#define MULTIPLIER 25
typedef struct HashTable
{
	int size;
	char* CodeTable[SIZE_TABLE];
}HashTable;
void init(HashTable* hashTable);
int hashCode(char* value);
void insert(HashTable* hashTable, char* value);
int find(HashTable* hashTable, char* value);

#endif // !_LZW_H
