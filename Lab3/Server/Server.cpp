// Server.cpp : Defines the entry point for the console application.
//

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "stdafx.h"
#include <iostream>
#include <ctime>
#include "conio.h"
#include "Winsock2.h"
#include "TCPConnection.h"
#pragma comment(lib, "WS2_32.lib")
#pragma warning (disable : 4996)

using namespace std;

int main() {
	setlocale(LC_CTYPE, "rus");

	WSADATA wsa;
	SOCKET sS;
	clock_t startTime, stopTime;

	try {
		//----------------------------------------1----------------------------------------
		if (WSAStartup(MAKEWORD(2, 0), &wsa) != 0)
			throw TCPConnection::Helper::SetErrorMsgText("Startup: ", WSAGetLastError());

		//----------------------------------------2----------------------------------------
		if ((sS = socket(AF_INET, SOCK_DGRAM, NULL)) == INVALID_SOCKET)
			throw TCPConnection::Helper::SetErrorMsgText("Socket: ", WSAGetLastError());

		SOCKADDR_IN serv;
		serv.sin_family = AF_INET; //используется IP-адресация
		serv.sin_addr.s_addr = INADDR_ANY; //любой собственный IP-адрес
		serv.sin_port = htons(2000); //порт

		if (bind(sS, (LPSOCKADDR)&serv, sizeof(serv)) == SOCKET_ERROR)
			throw TCPConnection::Helper::SetErrorMsgText("Bind: ", WSAGetLastError());

		//----------------------------------------3----------------------------------------
		char bfrom[50]; // буфер ввода
		int lobuf = 0;  // количество принятых байт
		int libuf = 0;  // количество отправленных байт
		int lc = sizeof(serv);

		startTime = clock();

		do {
			if ((lobuf = recvfrom(sS, bfrom, sizeof(bfrom), NULL, (sockaddr*)&serv, &lc)) == SOCKET_ERROR)
				throw TCPConnection::Helper::SetErrorMsgText("recv:", WSAGetLastError());

			Sleep(10);

			cout << "Количество полученых байт сообщения: " << lobuf << endl;
			cout << "Текст сообшения: " << bfrom << endl;

			//----------------------------------------4----------------------------------------
			/*
			if ((libuf = sendto(sS, bfrom, sizeof(bfrom), NULL, (sockaddr*)&serv, sizeof(serv))) == SOCKET_ERROR)
				throw TCPConnection::Helper::SetErrorMsgText("send:", WSAGetLastError());
				*/

		} while (lobuf != 0);

		//----------------------------------------5----------------------------------------
		stopTime = clock();
		cout << "Время выполнения (сек): " << (double)((stopTime - startTime) / CLK_TCK) << endl;

		if (closesocket(sS) == SOCKET_ERROR)
			throw TCPConnection::Helper::SetErrorMsgText("Closesocket: ", WSAGetLastError());
		if (WSACleanup() == SOCKET_ERROR)
			throw TCPConnection::Helper::SetErrorMsgText("Cleanup: ", WSAGetLastError());
	}
	catch (string errorMsg) {
		cout << endl << errorMsg << endl;
	}

	_getch();
    return 0;
}

