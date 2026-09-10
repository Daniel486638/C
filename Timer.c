#include <windows.h>
#include <stdio.h>

int main() {
	char Buffer[16];
    int Time;
    int Minutes;

    scanf("%s", Buffer);
    char *Array = strtok(Buffer, ":");
    Minutes = atoi(Array);
    Array = strtok(0, ":");
    if (Array) {
        Time = atoi(Array);
        Time += Minutes * 60;
    } else {
        Time = Minutes;
    };

	for (int i = 0; i <= Time; i++) {
		printf("%i:%i\n", (i - (i % 60)) / 60, i % 60);
		if (Time - 1 == i) {
			PlaySound("C:\\Users\\Daniel\\Documents\\Text Files\\Scripts\\C\\Win\\Executable\\Timer\\Sounds\\MarioJump.wav", NULL, SND_ASYNC | SND_LOOP | SND_FILENAME);
		};
		Sleep(1000);
	};
	getchar();
	getchar();

	return 0;
};