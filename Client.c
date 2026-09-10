#include <stdio.h>
#include <WinSock2.h>
#include <Ws2tcpip.h>
#include <locale.h>
#include <pthread.h>
#include <stdlib.h>
#define IP "127.0.0.1"

int Length;
sockaddr_in server;
SOCKET s;
char Buffer[128];

void *read(void*) {
	while (1) {
		if (recvfrom(s, Buffer, 128, 0, (sockaddr*)&server, &Length) >= 0) {
			for (int i = 0; i < 127; i++) {
				if (Buffer[i] == '\n') {
					Buffer[i] = '\0';
				};
			};
			wprintf(L"Сервер отправил: %ls\n", Buffer);
		};
	};
};

int main() {
	std::system("chcp 1251");
	char Ip[15];
	setlocale(LC_ALL, "Russian");
	// wprintf(L"Запишите сюда IP подключаемого.\n");
	// scanf("%s", Ip);
	WSAData Data;
	WSAStartup(0x202, &Data);

	server.sin_family = AF_INET;
	server.sin_port = htons(2437);
	inet_pton(AF_INET, IP, &server.sin_addr.s_addr);
	// printf("%i", server.sin_addr.s_addr);

	s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	Length = sizeof(server);
	char Send[25];
	pthread_t *TID = (pthread_t*)malloc(sizeof(pthread_t));
	pthread_create(TID, NULL, read, NULL);
	while (1) {
		fgets(Send, 25, stdin);
		const size_t Size = strlen(Send) + 1;
		wchar_t Send2[Size];
		mbstowcs(Send2, Send, Size);
		sendto(s, (const char*)Send2, Size * 2, 0, (sockaddr*)&server, Length);
	};

	getchar();
	getchar();

	free(TID);
	closesocket(s);
	WSACleanup();

	return 0;
};