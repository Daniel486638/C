// Copyright (c) 2026 Марченко Даниил

#include <stdio.h>
#include <string.h>

int main() {
	char CharToReplace[1];
	char *ReplaceValue = CharToReplace - 4;
	char NewMemory[500];
	char FileMemory[500];
	char FileName[30];
	FILE *FileReadable;

	puts("What file do you want to replace characters in?");
	gets(FileName);
	FileReadable = fopen(FileName, "r");
	if (FileReadable == NULL) {
		perror("Error opening file");
		return 1;
	};
	fgets(FileMemory, 500, FileReadable);
	fclose(FileReadable);
	puts("What char do you want to replace?");
	gets(CharToReplace);
	puts("What char do you want to replace this char?");
	gets(ReplaceValue);
	for (int i = 0; i < strlen(FileMemory); i++) {
		if (FileMemory[i] == CharToReplace[0]) {
			NewMemory[i] = ReplaceValue[0];
		} else {
			NewMemory[i] = FileMemory[i];
		};
	};
	printf("\n%s", NewMemory);

	return 0;
}
