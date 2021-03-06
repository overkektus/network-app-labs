// client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include "Winsock2.h"
#include "TCPConnection.h"
#pragma comment(lib, "WS2_32.lib")
#pragma warning (disable : 4996)

using namespace std;

bool GetServer(char*, short, struct sockaddr*, int*);

WSADATA wsaData;
SOCKET cS;
SOCKADDR_IN serv;

int main() {
	setlocale(LC_CTYPE, "rus");

	int sizeOfServ = sizeof(serv);
	short servPort = 2000;
	char* servName = "Hello";

	serv.sin_family = AF_INET;				 // используется IP-адресация
	serv.sin_port = htons(2000);		     // порт 2000
	serv.sin_addr.s_addr = INADDR_BROADCAST; // широковещание

	try {
		if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
			throw TCPConnection::Helper::SetErrorMsgText("WSAStartup: ", WSAGetLastError());

		if ((cS = socket(AF_INET, SOCK_DGRAM, NULL)) == INVALID_SOCKET)
			throw TCPConnection::Helper::SetErrorMsgText("Socket: ", WSAGetLastError());

		int optval = 1;
		if (setsockopt(cS, SOL_SOCKET, SO_BROADCAST, (char*)&optval, sizeof(int)) == SOCKET_ERROR)
			throw TCPConnection::Helper::SetErrorMsgText("Setsockopt: ", WSAGetLastError());

		if (GetServer(servName, servPort, (sockaddr*)&serv, &sizeOfServ)) {
			cout << "IP-адрес сервера: " << inet_ntoa(serv.sin_addr) << endl;
			cout << "Порт:             " << serv.sin_port << endl;
		}

		if (closesocket(cS) == SOCKET_ERROR)
			throw TCPConnection::Helper::SetErrorMsgText("Closesocket: ", WSAGetLastError());

		if (WSACleanup() == SOCKET_ERROR)
			throw TCPConnection::Helper::SetErrorMsgText("WSACleanup: ", WSAGetLastError());
	}
	catch (string errorMessage) {
		cout << errorMessage << endl;
	}
	_getch();
    return 0;
}

bool GetServer(char* name, short port, struct sockaddr* from, int* flen) {
	int countOfSendedBytes = 0;
	int countOfReceivedBytes = 0;
	char msgFromServer[50];

	memset(&msgFromServer, 0, sizeof(msgFromServer));

	if ((countOfSendedBytes = sendto(cS, name, strlen(name), NULL, (sockaddr*)&serv, sizeof(serv))) == SOCKET_ERROR)
		throw TCPConnection::Helper::SetErrorMsgText("Sendto: ", WSAGetLastError());

	if ((countOfReceivedBytes = recvfrom(cS, msgFromServer, sizeof(msgFromServer), NULL, from, flen)) == SOCKET_ERROR)
		throw TCPConnection::Helper::SetErrorMsgText("Recvfrom: ", WSAGetLastError());

	cout << "Ответ от сервера: " << msgFromServer << endl << endl;

	return (strcmp(name, msgFromServer) == 0);
}