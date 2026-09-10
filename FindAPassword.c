// Copyright (c) 2026 Марченко Даниил

#include <stdio.h>
#include <string.h>

int main() {
	char Password[] = "Simple"; // Array allows one to change the string//char *Password = "Simple";
	char UserInput[strlen(Password)];

	char String[] = "GladlyAcceptMe";
	int Correct = 0;
	while (!Correct) {
		printf("Enter a password.\n%p\n%p\n", Password, &Password);
		gets(UserInput);
		printf("Interesting variable: %s.\n", String);
		if (strcmp(UserInput, Password) == 0) {
			printf("Correct!");
			Correct = 1;
		} else {
			printf("Wrong!");
		};
	};
	getchar();
	return 0;
}
