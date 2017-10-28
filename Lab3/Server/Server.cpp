// Server.cpp : Defines the entry point for the console application.
//

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "stdafx.h"
#include <iostream>
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

		if ((lobuf = recv(sS, bfrom, sizeof(bfrom), NULL)) == SOCKET_ERROR)
			throw TCPConnection::Helper::SetErrorMsgText("recv:", WSAGetLastError());

		cout << bfrom << endl;

		//----------------------------------------4----------------------------------------

		//----------------------------------------5----------------------------------------
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

