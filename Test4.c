// Copyright (c) 2026 Марченко Даниил

#include <stdio.h>

int main() {
	/*for (int i = 0; i < 100; i ++) {
		printf("%i\n", *((int*)(0x00FFFFFFFFFFFFFF + i)));
	};*/
	int A = 2;
	printf("%i\n", *((int*)(0x00000000000000FF)));
	return 0;
};
