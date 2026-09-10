// Copyright (c) 2026 Марченко Даниил

#include <stdio.h>
#include <string.h>

int main() {
	FILE *NewFile;
	char FileName[20];
	puts("Name your file.");
	gets(FileName);
	NewFile = fopen(FileName, "w");
	puts("Say something. exit() to exit.");
	char F = 0;
	while (1) {
		char InputLine[25];
		gets(InputLine);
		if (strcmp(InputLine, "exit()") == 0) {
			break;
		};
		if (F) {
			fprintf(NewFile, "\n");
		};
		fprintf(NewFile, InputLine);
		F = 1;
	};
	fclose(NewFile);

	return 0;
};
