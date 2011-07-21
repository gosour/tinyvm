#include "tvm_file.h"

FILE* tvm_fopen(const char* filename, const char* extension, const char* mode)
{
	FILE* pFile;
	size_t fname_chars = strlen(filename) + strlen(extension) + 1;
	char* fname = malloc(sizeof(char) * fname_chars);

	strcpy(fname, filename);

	pFile = fopen(fname, mode);

	if(!pFile)
	{
		strcat(fname, extension);
		pFile = fopen(fname, mode);
	}

	free(fname);
	return pFile;
}

void tvm_fclose(FILE* f)
{
	fclose(f);
}

int tvm_fcopy(char* dest, size_t size, FILE* src)
{
	int i;

	fpos_t pos;
	fgetpos(src, &pos);

	for(i = 0; i < size && !feof(src); i++)
	{
		dest[i] = fgetc(src);
	}

	fsetpos(src, &pos);

	return 0;
}

int tvm_flength(FILE* f)
{
	int length = 0;

	fpos_t pos;
	fgetpos(f, &pos);

	while(!feof(f))
	{
		fgetc(f);
		length++;
	}

	fsetpos(f, &pos);

	return length;
}
