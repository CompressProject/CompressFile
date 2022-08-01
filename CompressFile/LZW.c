#include "decompress_LZW.h"
#pragma region hashTable
//represent the code table.

void init(HashTable* hashTable)
{
	//what with the Hebrew language?
	hashTable->size = 256;
	for (int i = 0; i < 256; i++)
	{
		char str[10] = { (char)i, "\0" };
		hashTable->CodeTable[i] = _strdup(str);
	}
	for (int i = 256; i < SIZE_TABLE; i++)
	{
		hashTable->CodeTable[i] = NULL;
	}
}
int hashCode(char* value)
{
	printf("hashCode value= %c", value);
	long key;
	const char* currentChar;
	currentChar = (const char*)value;
	key = 1;
	if (value[1] == '\0')
		return value[0];
	while (*currentChar != '\0')
	{
		key = key * MULTIPLIER + *currentChar;
		currentChar++;
	}
	key = key % SIZE_TABLE;
	if (key < 256)
		key += 256;
	return key;
}
void insert(HashTable* hashTable, char* value)
{
	if (hashTable->size > SIZE_TABLE - 1)
		return;
	//calculate hash key.
	int key = hashCode(value);
	//check if hashTable->CodeTable[key] is full and increase the key until arrived to empty place.
	while (hashTable->CodeTable[key])
	{
		key++;
		key %= SIZE_TABLE;
	}
	//insert the value to the table.
	hashTable->CodeTable[key] = value;
	hashTable->size++;
}
int find(HashTable* hashTable, char* value)
{
	printf("find value= %c", value);
	//calculate hash key.
	int hashIndex = hashCode(value), firstKey = hashIndex;
	// Find the value with given key .
	while (hashTable->CodeTable[hashIndex] != NULL && strcmp(hashTable->CodeTable[hashIndex], value) != 0)
	{
		hashIndex++;
		hashIndex %= SIZE_TABLE;
		if (firstKey == hashIndex)
			return -1;
	}
	//if  found return hashIndex.
	if (hashTable->CodeTable[hashIndex] != NULL && strcmp(hashTable->CodeTable[hashIndex], value) == 0)
		return hashIndex;
	// If not found return -1.
	return -1;
}
#pragma endregion