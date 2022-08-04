#ifndef  _DecompressLZD_H
#define _DecompressLZD_H
#include "LZW.h"
void decompressLZW(char*);
int readFourCharactersFromFile(FILE*);
int checkCodeValidation(int);

#endif // ! _DecompressLZD_H