#include "Test.h"
void test()
{
	int resultCompare;
	char* arrsource[SIZE] = {
		"C:\\γρι\\project_compress\\emptyFile.txt",
		"C:\\γρι\\project_compress\\word.txt",
		"C:\\γρι\\project_compress\\huffman.txt",
	};
	char* arrCompressed[SIZE] = {
		"C:\\γρι\\CompressFile\\CompressFile\\result1.bin",
		"C:\\γρι\\CompressFile\\CompressFile\\result2.bin",
		"C:\\γρι\\CompressFile\\CompressFile\\result3.bin"
	};
	char* arrDes[SIZE] = {
		"C:\\γρι\\CompressFile\\CompressFile\\originalDataEmptyFile.txt",
		"C:\\γρι\\CompressFile\\CompressFile\\originalDataSmallFile.txt",
		"C:\\γρι\\CompressFile\\CompressFile\\originalDataBigFile.txt"
	};
	checkSmallFile("C:\\γρι\\project_compress\\word.txt", "C:\\γρι\\CompressFile\\CompressFile\\resultSmallFile.bin", "C:\\γρι\\CompressFile\\CompressFile\\originalDataSmallFile.txt");
	checkEmptyFile("C:\\γρι\\project_compress\\emptyFile.txt", "C:\\γρι\\CompressFile\\CompressFile\\resultEmptyFile.bin", "C:\\γρι\\CompressFile\\CompressFile\\originalDataEmptyFile.txt");
	checkBigFile("C:\\γρι\\project_compress\\huffman.txt", "C:\\γρι\\CompressFile\\CompressFile\\resultBigFile.bin", "C:\\γρι\\CompressFile\\CompressFile\\originalDataBigFile.txt");
	//checkNotExistsFile("C:\\γρι\\project_compress\\notExist.txt", "C:\\γρι\\CompressFile\\CompressFile\\resultNotExistsFile.bin", "C:\\γρι\\CompressFile\\CompressFile\\originalDataNotExistsFile.txt");
	for (int i = 0; i < SIZE; i++)
	{
		resultCompare=compareFiles(arrsource[i],arrDes[i]);
		printf("resultCompare: %d\n", resultCompare);
	}
}
void checkSmallFile(char* PathSource, char* PathCompressed, char* PathDecompressed)
{
	compressLZW(PathSource, PathCompressed);
	decompressLZW(PathCompressed, PathDecompressed);
}
void checkEmptyFile(char* PathSource, char* PathCompressed, char* PathDecompressed)
{
	compressLZW(PathSource, PathCompressed);
	decompressLZW(PathCompressed, PathDecompressed);
}
void checkBigFile(char* PathSource, char* PathCompressed, char* PathDecompressed)
{
	compressLZW(PathSource, PathCompressed);
	decompressLZW(PathCompressed, PathDecompressed);
}
void checkNotExistsFile(char* PathSource, char* PathCompressed, char* PathDecompressed)
{
	compressLZW(PathSource, PathCompressed);
	decompressLZW(PathCompressed, PathDecompressed);
}
void readFromTheFile(FILE* file, char** contentFile, long* numbytes)
{
	fseek(file, 0, SEEK_END);
	*numbytes = ftell(file);
	fseek(file, 0, SEEK_SET);
	*contentFile = (char*)malloc((*numbytes) * sizeof(char) + 1);
	if (contentFile == NULL)
		return 1;
	fread(*contentFile, sizeof(char), *numbytes, file);
}
int compareFiles(char* pathSource, char* pathDecompressed)
{
	FILE* filesSource;
	FILE* filesDecompressed;
	char ch;
	char* contentSourceFile = NULL, * contentDesFile = NULL;
	long numbytesSource, numbytesDes;
	int result;
	filesSource = fopen(pathSource, "r");
	filesDecompressed = fopen(pathDecompressed, "r");
	readFromTheFile(filesSource, &contentSourceFile, &numbytesSource);
	readFromTheFile(filesDecompressed, &contentDesFile, &numbytesDes);
	result = memcmp(contentSourceFile, contentDesFile, numbytesSource);
	fclose(filesSource);
	return result;
}
void utcheckHuffmanTree()
{
	/*buildfrequencyArray(intermediateFile, frequencyArray);
	MinHeapNode* root = buildHuffmanTree(data, frequencyArray, size);
	writeTreeToDecompressFile(decompressFile, root);*/
}
