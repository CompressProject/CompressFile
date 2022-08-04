#ifndef __CommonFunction_H
#define __CommonFunctions_H
#define _CRT_SECURE_NO_WARNINGS

#define SIZE_TABLE 4096
#define MULTIPLIER 17
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char* convertIntToChar(int);
char* append(char*, char);
int stringLength(char*);
int intLength(int);
void convertIntToBinary(char*);
void readBinaryFile(char*);

#endif // !__CommonFunction_H