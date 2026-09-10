// Copyright (c) 2026 Марченко Даниил

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define SIZE 255

int main() {
	system("chcp 1251");
	setlocale(LC_ALL, "Russian");

	FILE *NewFile;
	char FileName[SIZE + 1];

	wprintf(L"Пожалуйста, напишите имя файла, включая его расширение.\n");
	fgets(FileName, SIZE, stdin);

	for (int i = 0; i < SIZE; i++) {
		if (FileName[i] == '\n') {
			FileName[i] = '\0';
			break;
		};
	};

	if ((NewFile = fopen(FileName, "r"))) {
		wprintf(L"Файл уже существует!\n");
		fgets(FileName, SIZE, stdin);
	} else {
		NewFile = fopen(FileName, "w");
	};

	fclose(NewFile);

	return 0;
};
