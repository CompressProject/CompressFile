

void main(char** argv)
{
	//C:\\דסי\\project_compress\\result.txt
	//C:\\דסי\\project_compress\\bigFile.txt
	//"C:\\דסי\\project_compress\\word.docx"
	// "C:\\דסי\\project_compress\\CompressFile_full\\CompressFile\\CompressFile.c"
	//compressLZW(argv[1], argv[2]);
	compressLZW("C:\\דסי\\project_compress\\bigFile.txt", "C:\\דסי\\CompressFile\\CompressFile\\result.bin");
	decompressLZW("C:\\דסי\\CompressFile\\CompressFile\\result.bin", "C:\\דסי\\CompressFile\\CompressFile\\originalData.txt");
	//compressHuffman("C:\\דסי\\CompressFile\\CompressFile\\result.txt", " ");
}
