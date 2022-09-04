#include "CommonFunction.h"
char* convertIntToChar(int num)
{
	int length = intLength(num);
	char* result = (char*)malloc(length);
	sprintf(result, "%d", num);
	return result;
}
char* append(char* string, char c) {
	int length = stringLength(string);
	char* concatenatedString = (char*)malloc(length + 2);
	if (!concatenatedString)
	{
		printf("unable to allocate memory.");
		exit(1);
	}
	strcpy(concatenatedString, string);
	concatenatedString[length] = c;
	concatenatedString[length + 1] = '\0';
	return concatenatedString;
}
char* appendFromBegin(char* string, char c) {
	int length = stringLength(string);
	char* concatenatedString = (char*)malloc(length + 2);
	if (!concatenatedString)
	{
		printf("unable to allocate memory.");
		exit(1);
	}
	concatenatedString[0] = c;
	strcpy(concatenatedString + 1, string);
	concatenatedString[length + 1] = '\0';
	return concatenatedString;
}
int stringLength(char* p)
{
	int count = 0;
	while ((*p) != '\0')
	{
		count++;
		p++;
	}
	return count;
}
int intLength(int number) {
	if (number == 0)
		return 1;
	int count = 0;
	while (number != 0) {
		number /= 10;
		count++;
	}
	return count;
}
int combineTwoNumbers(int codeChar, int prevCodeChar,int shiftLengh)
{
	/*101= 110 0101
	101<<12 = 110 0101 0000 0000 0000
	 68 =100 0100
	res= 110 0101 0000 0100 0100*/
	codeChar <<= shiftLengh;
	return codeChar | prevCodeChar;
}
