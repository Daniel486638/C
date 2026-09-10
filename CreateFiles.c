// Copyright (c) 2026 Марченко Даниил

#include <stdio.h>
#include <string.h>

int main(int ArgsLength, char **Args) {
	FILE *NewFile;
	char FileName[20];
	while (1) {
		gets(FileName); //fgets(FileName, 20, stdin);
		if (strcmp(FileName, "exit()") == 0) {
			break;
		};
		NewFile = fopen(FileName, "w");
		fclose(NewFile);
	};

	return 0;
};
