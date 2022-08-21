#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define SIZE_TABLE 4096
#define MULTIPLIER 17
#define LENGTH_CODE 12
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <stdbool.h>
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
