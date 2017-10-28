// Client.cpp : Defines the entry point for the console application.
//

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
	SOCKET cC;

	try {
		//----------------------------------------1----------------------------------------
		if (WSAStartup(MAKEWORD(2, 0), &wsa) != 0)
			throw TCPConnection::Helper::SetErrorMsgText("Startup: ", WSAGetLastError());

		//----------------------------------------2----------------------------------------
		if ((cC = socket(AF_INET, SOCK_DGRAM, NULL)) == INVALID_SOCKET)
			throw TCPConnection::Helper::SetErrorMsgText("Socket: ", WSAGetLastError());

		//----------------------------------------3----------------------------------------
		SOCKADDR_IN serv;
		serv.sin_family = AF_INET;
		serv.sin_port = htons(2000);
		//serv.sin_addr.s_addr = inet_addr("192.168.43.234");
		serv.sin_addr.s_addr = inet_addr("127.0.0.1");

		char obuf[50] = "client: I here"; // буфер вывода
		int lobuf = 0; // количество отправленных

		if ((lobuf = sendto(cC, obuf, strlen(obuf) + 1, NULL, (sockaddr*)&serv, sizeof(serv))) == SOCKET_ERROR)
			throw TCPConnection::Helper::SetErrorMsgText("recv:", WSAGetLastError());

		//----------------------------------------5----------------------------------------
		if (WSACleanup() == SOCKET_ERROR)
			throw TCPConnection::Helper::SetErrorMsgText("Cleanup: ", WSAGetLastError());
	}
	catch (string errorMsg) {
		cout << endl << errorMsg << endl;
	}

	_getch();

	return 0;
}