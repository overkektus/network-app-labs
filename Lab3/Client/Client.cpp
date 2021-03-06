// Client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <ctime>
#include "conio.h"
#include "Winsock2.h"
#include "TCPConnection.h"
#pragma comment(lib, "WS2_32.lib")
#pragma warning (disable : 4996)

using namespace std;

void prepareString(string& str, int i);

int main() {
	setlocale(LC_CTYPE, "rus");

	WSADATA wsa;
	SOCKET cC;
	int countMsg;
	clock_t startTime, stopTime;

	try {
		//----------------------------------------1----------------------------------------
		if (WSAStartup(MAKEWORD(2, 0), &wsa) != 0)
			throw TCPConnection::Helper::SetErrorMsgText("Startup: ", WSAGetLastError());

		//----------------------------------------2----------------------------------------
		if ((cC = socket(AF_INET, SOCK_DGRAM, NULL)) == INVALID_SOCKET)
			throw TCPConnection::Helper::SetErrorMsgText("Socket: ", WSAGetLastError());

		cout << "Количество сообщений: ";
		cin >> countMsg; cout << endl;


		//----------------------------------------3----------------------------------------
		SOCKADDR_IN clnt;
		clnt.sin_family = AF_INET;
		clnt.sin_port = htons(2000);
		//serv.sin_addr.s_addr = inet_addr("192.168.43.234");
		clnt.sin_addr.s_addr = inet_addr("127.0.0.1");

		char obuf[50] = "Hello"; // буфер вывода
		string bufStr;
		int lc = sizeof(clnt);
		int lobuf = 0; // количество отправленных

		startTime = clock();

		for (int i = 0; i < countMsg; i++) {
			if ((lobuf = sendto(cC, obuf, strlen(obuf) + 1, NULL, (sockaddr*)&clnt, sizeof(clnt))) == SOCKET_ERROR)
				throw TCPConnection::Helper::SetErrorMsgText("recv:", WSAGetLastError());

			cout << "Количество отправленый байт: " << lobuf << endl;
			cout << "Текст сообшения: " << obuf << endl;

			/*
			if ((lobuf = recvfrom(cC, obuf, sizeof(obuf), NULL, (sockaddr*)&clnt, &lc)) == SOCKET_ERROR)
				throw TCPConnection::Helper::SetErrorMsgText("recv:", WSAGetLastError());
			*/
			/*
			bufStr = (string)obuf;
			prepareString(bufStr, i + 1);
			strcpy(obuf, bufStr.c_str());
			*/
		}
	
		stopTime = clock();
		cout << "Время выполнения (сек): " << (double)((stopTime - startTime) / CLK_TCK) << endl;

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

void prepareString(string& str, int i) {
	str.erase(18);
	if (i < 10) {
		str.append("00");
		str.append(to_string(i));
	}
	else if (i < 100) {
		str.append("0");
		str.append(to_string(i));
	}
	else
		str.append(to_string(i));
}