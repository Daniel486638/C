// Copyright (c) 2026 Марченко Даниил

#include <stdio.h>
#include <string.h>

int main(int ArgsLength, char **Args) {
	FILE *NewFile;
	char *FileName = Args[1];
	NewFile = fopen(FileName, "w");
	fclose(NewFile);

	return 0;
};
