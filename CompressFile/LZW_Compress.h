#pragma once
#include "DataStructuresLZW.h";
//read binary file.
void readBinaryFile(char* binaryFilePath);
//compress the file using the lzw method.
void compressLZW(char*, char*);