#pragma once
#include "DataStructuresLZW.h";
//read binary file.
void readBinaryFile(char* binaryFilePath);
//combine two codes into one variable to insert to the file.
int combineTwoNumbers(codeChar, prevCodeChar);
//compress the file using the lzw method.
void compressLZW(char*, char*);