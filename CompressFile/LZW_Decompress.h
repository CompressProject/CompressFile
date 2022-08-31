#pragma once
#include "DataStructuresLZW.h"
//decompress the file using the lzw method.
void decompressLZW(char* decompressionPath, char* resultPath);
//Decomposes the code pair into two variables.
void unCombineTwoNumbers(int , int* , int* );
//Read a pair of codes from the file.
int readCharactersFromFile(FILE*, int*, int*);
//check the validation of the code.
int checkCodeValidation(int);
//read from binary file.
void read(char* binaryFilePath);
