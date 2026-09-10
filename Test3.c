#include <stdio.h>

int main() {
	int Var = 7;
	int Var2 = 102547;
	printf("%p, %i, %i", &Var, Var, Var2);
	getchar();
	printf("%i, %i", Var, Var2);
	getchar();

	return 0;
};