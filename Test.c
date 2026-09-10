// Copyright (c) 2026 Марченко Даниил

#include <stdio.h>
#include <stdlib.h>
#define PrintMemory printf("%p %i\n%p %i\n%p %p %i\n", &Variable1, Variable1, &Variable2, Variable2, &Pointer, Pointer, *Pointer);

void Func1();
void Func2(int);
void Func3(int Heh) {
	printf("%d\n", Heh);
};
int Func4();

int main() {
	int Variable;
	int Variable1 = 7;
	int Variable2 = 8;
	int *Pointer = &Variable1;
	
	Func1();
	Func2(9);
	Func3(10);
	Func4();
	
	PrintMemory;
	
	int *AV = calloc(12, 4);
	int *AV2 = calloc(12, 4);
	
	printf("%p, %p\n", AV, AV2);
	
	puts("Enter any character to continue...");
	getchar();
	PrintMemory;

	return 0;
}

void Func1() {
	printf("%%rbp\n");
};

void Func2(int i) {
	printf("%d\n", i);
};

int Func4() {
	return 3.14;
};
