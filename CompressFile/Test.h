#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#define SIZE 3
//the main function to test the code.
void test();

//compress and decompress different types of files.
void checkSmallFile(char* PathSource, char* PathCompressed, char* PathDecompressed);
void checkBigFile(char* PathSource, char* PathCompressed, char* PathDecompressed);
void checkNotExistsFile(char* PathSource, char* PathCompressed, char* PathDecompressed);
void checkEmptyFile(char* PathSource, char* PathCompressed, char* PathDecompressed);

//Compares the contents of the source file to the decompressed file.
int compareFiles(char* pathSource, char* pathDecompressed);

//read all the data from the file.
void readFromTheFile(FILE* file, char** contentFile, long* numbytes);
