#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main(int ArgLength, char **Args) {
	printf("%s", Args[0]);
	Sleep(4000);
	system("./Recursion.exe");
	while (1) {Sleep(1000);};
	return 0;
}