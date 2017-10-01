// Client.cpp : Defines the entry point for the console application.
//

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <string>
#include <iostream>
#include "conio.h"
#include "Winsock2.h"
#include "../Serv/TCPConnection.h"
#pragma comment(lib, "WS2_32.lib")

using namespace std;


int main()
{
	setlocale(LC_CTYPE, "rus");

	WSADATA wsa;
	SOCKET cC;

	try {
		if (WSAStartup(MAKEWORD(2, 0), &wsa) != 0)
			throw TCPConnection::Helper::SetErrorMsgText("Startup: ", WSAGetLastError());

		if ((cC = socket(AF_INET, SOCK_STREAM, NULL)) == INVALID_SOCKET)
			throw TCPConnection::Helper::SetErrorMsgText("Socket: ", WSAGetLastError());

		SOCKADDR_IN serv;
		serv.sin_family = AF_INET;
		serv.sin_port = htons(2000);
		//serv.sin_addr.s_addr = inet_addr("192.168.43.234");
		serv.sin_addr.s_addr = inet_addr("127.0.0.1");
		if ((connect(cC, (sockaddr*)&serv, sizeof(serv))) == SOCKET_ERROR)
			throw TCPConnection::Helper::SetErrorMsgText("Connect: ", WSAGetLastError());


		char obuf[50] = "Hello from client "; // буфер вывода

		for (int i = 0; i < 1000; i++) {
			int lobuf = 0; // количество отправленных
			if ((lobuf = sendto(cC, obuf, strlen(obuf) + 1, NULL, (sockaddr*)&serv, sizeof(serv))) == SOCKET_ERROR)
				throw TCPConnection::Helper::SetErrorMsgText("Recv: ", WSAGetLastError());
		}

		
		//Закрытие библиотеки
		if (closesocket(cC) == SOCKET_ERROR)
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