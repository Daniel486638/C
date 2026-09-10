#include <stdio.h>

int main() {
	int Var = 7;
	printf("%p, %i", &Var, Var);
	getchar();
	printf("%i", Var);
	getchar();

	return 0;
};