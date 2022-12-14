#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define SIZE_TABLE 4095
#define MULTIPLIER 17
#define LENGTH_CODE 12
#define LENGTH_READ_CODE 3*sizeof(char)
#define LENGTH_CODE_IN_BIT 3
#define PRINT_COMPRESS 
#define PRINT_DECOMPRESS 
#define SIGN 4095
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <stdbool.h>
FILE* compressPrintFile;
FILE* decompressPrintFile;
FILE* compressHuffmanPrintFile;
//convert int to char(not by the ascii code!).
char* convertIntToChar(int);
//Concatenate a character into a string.
char* append(char*, char);
//Concatenate a character into a string from the begining.
char* appendFromBegin(char*, char);
//return the length of the string.
int stringLength(char*);
//return the length of the number.
int intLength(int);
//combine two codes into one variable to insert to the file.
int combineTwoNumbers(int codeChar, int prevCodeChar, int shiftLengh);
