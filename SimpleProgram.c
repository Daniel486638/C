#include <stdio.h>
#include <windows.h>

int main() {
	char String[] = "Hello! Is anyone there? Can anyone read me? Can anyone rewrite me?";

	while (1) {
		printf("%s\n", String);
		Sleep(5000);
	};

	return 0;
}