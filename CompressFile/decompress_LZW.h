#ifndef  _DecompressLZD_H
#define _DecompressLZD_H
#include "LZW.h"
void decompressLZW(char* path);
int readFourCharactersFromFile(FILE*);
int checkCodeValidation(int code);

#endif // ! _DecompressLZD_H