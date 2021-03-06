// server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include "Winsock2.h"
#include "TCPConnection.h"
#pragma comment(lib, "WS2_32.lib")
#pragma warning (disable : 4996)

using namespace std;

bool GetRequestFromClient(char*, short, struct sockaddr*, int*);
bool PutAnswerToClient(char*, struct sockaddr*, int*);
void FindTheSameServer(char* name);

WSADATA wsaData;
SOCKET sS;
SOCKADDR_IN serv;
SOCKADDR_IN clnt;

int main() {
	setlocale(LC_CTYPE, "rus");

	int sizeOfСlnt = sizeof(clnt);
	short port = 1000;
	char* servName = "Hello";

	serv.sin_family = AF_INET;		   // используется IP-адресация
	serv.sin_port = htons(port);	   // порт 2000
	serv.sin_addr.s_addr = INADDR_ANY; // любой IP-адрес

	try {
		if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
			throw TCPConnection::Helper::SetErrorMsgText("WSAStartup: ", WSAGetLastError());

		FindTheSameServer(servName);

		if ((sS = socket(AF_INET, SOCK_DGRAM, NULL)) == INVALID_SOCKET)
			throw TCPConnection::Helper::SetErrorMsgText("Socket: ", WSAGetLastError());

		if (bind(sS, (LPSOCKADDR)&serv, sizeof(serv)) == SOCKET_ERROR)
			throw TCPConnection::Helper::SetErrorMsgText("Bind: ", WSAGetLastError());

		while (true) {
			
			while (!GetRequestFromClient(servName, port, (sockaddr*)&clnt, &sizeOfСlnt)) {}
			
			PutAnswerToClient(servName, (sockaddr*)&clnt, &sizeOfСlnt);

			cout << "IP-адрес клиента: " << inet_ntoa(clnt.sin_addr) << endl;
			cout << "Порт:             " << clnt.sin_port << endl;
			cout << endl;
		}

		if (closesocket(sS) == SOCKET_ERROR)
			throw TCPConnection::Helper::SetErrorMsgText("Closesocket: ", WSAGetLastError());

		if (WSACleanup() == SOCKET_ERROR)
			throw TCPConnection::Helper::SetErrorMsgText("WSACleanup: ", WSAGetLastError());
	}
	catch (string errorMessage) {
		cout << errorMessage << endl;
	}
    return 0;
}


bool GetRequestFromClient(char* name, short port, struct sockaddr* from, int* flen) {
	char msgFromClnt[50];
	int countOfRecievedBytes = 0;

	memset(&msgFromClnt, 0, sizeof(msgFromClnt));

	if ((countOfRecievedBytes = recvfrom(sS, msgFromClnt, sizeof(msgFromClnt), NULL, from, flen)) == SOCKET_ERROR)
		throw TCPConnection::Helper::SetErrorMsgText("Recvfrom: ", WSAGetLastError());

	return (strcmp(name, msgFromClnt) == 0);
}

bool PutAnswerToClient(char* name, struct sockaddr* to, int *lto) {
	int countOfSendedBytes = 0;

	if ((countOfSendedBytes = sendto(sS, name, strlen(name), NULL, to, *lto)) == SOCKET_ERROR)
		throw TCPConnection::Helper::SetErrorMsgText("Sendto: ", WSAGetLastError());

	return countOfSendedBytes > 0;
}

void FindTheSameServer(char* name) {
	SOCKET bS;
	SOCKADDR_IN broadcast;
	SOCKADDR_IN sameServ;
	int sameServSizeOf = sizeof(sameServ);

	broadcast.sin_family = AF_INET;
	broadcast.sin_port = htons(2000);
	broadcast.sin_addr.s_addr = INADDR_BROADCAST;

	char msgFromServ[50];
	memset(&msgFromServ, 0, sizeof(msgFromServ));

	if ((bS = socket(AF_INET, SOCK_DGRAM, NULL)) == INVALID_SOCKET)
		throw TCPConnection::Helper::SetErrorMsgText("Socket: ", WSAGetLastError());

	int optval = 1;
	if (setsockopt(bS, SOL_SOCKET, SO_BROADCAST, (char*)&optval, sizeof(int)) == SOCKET_ERROR)
		throw TCPConnection::Helper::SetErrorMsgText("Setsockopt: ", WSAGetLastError());

	int timeout = 3000;
	if (setsockopt(bS, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout)) == SOCKET_ERROR)
		throw TCPConnection::Helper::SetErrorMsgText("Setsockopt: ", WSAGetLastError());


	if (sendto(bS, name, strlen(name), NULL, (sockaddr*)&broadcast, sizeof(broadcast)) == SOCKET_ERROR)
		throw TCPConnection::Helper::SetErrorMsgText("Sendto: ", WSAGetLastError());

	if (recvfrom(bS, msgFromServ, sizeof(msgFromServ), NULL, (sockaddr*)&sameServ, &sameServSizeOf) == SOCKET_ERROR) {
		if (WSAGetLastError() == WSAETIMEDOUT) {
			cout << "Сервер с таким же позывным не найден" << endl << endl;
			return;
		}
		throw TCPConnection::Helper::SetErrorMsgText("Recvfrom: ", WSAGetLastError());
	}

	if (strcmp(msgFromServ, name) == 0) {
		cout << "Найден серевер с таким же позывным" << endl;
		cout << "IP-адрес: " << inet_ntoa(sameServ.sin_addr) << endl << endl;
	}

	if (closesocket(bS) == SOCKET_ERROR)
		throw TCPConnection::Helper::SetErrorMsgText("Closesocket: ", WSAGetLastError());
}