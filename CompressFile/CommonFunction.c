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
	strcpy(concatenatedString, string);
	concatenatedString[length] = c;
	concatenatedString[length + 1] = '\0';
	return concatenatedString;
}
char* appendFromBegin(char* string, char c) {
	//printf("string= %c\n", string);
	//puts(string);
	int length = stringLength(string);
	char* concatenatedString = (char*)malloc(length + 2);
	concatenatedString[0] = c;
	strcpy(concatenatedString + 1, string);
	concatenatedString[length + 1] = '\0';
	return concatenatedString;
}

int stringLength(char* p)
{
	//printf("the length of %c = ", p);
	int count = 0;
	while ((*p) != '\0')
	{
		count++;
		p++;
	}
	//printf("%d\n", count);
	return count;
}
int intLength(int number) {
	//printf("the length of %d = ", number);
	if (number == 0)
		return 1;
	int count = 0;
	while (number != 0) {
		number /= 10;
		count++;
	}
	//printf("%d\n", count);
	return count;
}
