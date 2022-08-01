#include "Common_Functions.h"

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
	strcpy(concatenatedString, string);
	concatenatedString[length] = c;
	concatenatedString[length + 1] = '\0';
	return concatenatedString;
}
int stringLength(char* p)
{
	printf("the length of %s = ", p);
	int count = 0;
	while (*p != '\0')
	{
		count++;
		p++;
	}
	printf("%d\n", count);
	return count;
}
int intLength(int number) {
	printf("the length of %d = ", number);
	if (number == 0)
		return 1;
	int count = 0;
	while (number != 0) {
		number /= 10;
		count++;
	}
	printf("%d\n", count);
	return count;
}