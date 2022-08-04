#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#define SIZE_TABLE 4096
#define MULTIPLIER 3
char* convertIntToChar(int);
char* append(char*, char);
char* appendFromBegin(char*, char);
int stringLength(char*);
int intLength(int);
