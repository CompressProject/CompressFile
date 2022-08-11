#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <stdbool.h>
#define SIZE_TABLE 4096
#define MULTIPLIER 17
#define LENGTH_CODE 12
char* convertIntToChar(int);
char* append(char*, char);
char* appendFromBegin(char*, char);
int stringLength(char*);
int intLength(int);
