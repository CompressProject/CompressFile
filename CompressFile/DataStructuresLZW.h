#include "CommonFunction.h"
//represent the code table.
typedef struct HashTable
{
	int size;
	char* CodeTable[SIZE_TABLE];
}HashTable;
//Initialize the first 256 places according to their ASCII code.
void init(HashTable*);
//generate a code.
int hashCode(char*);
//insert new sequence to the hash table.
void insert(HashTable*, char*);
//Searches if the sequence exists in the table.
int find(HashTable*, char*);

