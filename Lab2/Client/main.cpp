// Client.cpp : Defines the entry point for the console application.
//

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <string>
#include <iostream>
#include "conio.h"
#include "Winsock2.h"
#include "../Serv/TCPConnection.h"
#pragma comment(lib, "WS2_32.lib")
#pragma warning (disable : 4996)

using namespace std;

void prepareString(string& str, int i);

int main()
{
	setlocale(LC_CTYPE, "rus");

	WSADATA wsa;
	SOCKET cC;
	int countMsg;

	try {
		//----------------------------------------1----------------------------------------
		//»нициализаци€ WS2_32.DLL
		if (WSAStartup(MAKEWORD(2, 0), &wsa) != 0)
			throw TCPConnection::Helper::SetErrorMsgText("Startup: ", WSAGetLastError());

		//----------------------------------------2----------------------------------------
		//создание сокета и установка его параметров. сокет будет использоватьс€ дл€ соединени€
		//(сокет, ориентированный на поток)
		if ((cC = socket(AF_INET, SOCK_STREAM, NULL)) == INVALID_SOCKET)
			throw TCPConnection::Helper::SetErrorMsgText("Socket: ", WSAGetLastError());

		//----------------------------------------3----------------------------------------
		//connect предназначенна€ дл€ установки соединени€ с сокетом сервера.
		//в качестве параметров имеет созданный в предыдущем блоке дескриптор сокета,
		//ориентированного на поток, и структуру SOCKADDR_IN с параметрами сокета сервера.
		SOCKADDR_IN serv;
		serv.sin_family = AF_INET;
		serv.sin_port = htons(2000);
		//serv.sin_addr.s_addr = inet_addr("192.168.43.234");
		serv.sin_addr.s_addr = inet_addr("127.0.0.1");
		if ((connect(cC, (sockaddr*)&serv, sizeof(serv))) == SOCKET_ERROR)
			throw TCPConnection::Helper::SetErrorMsgText("Connect: ", WSAGetLastError());

		cout << " оличество сообщений: ";
		cin >> countMsg; cout << endl;

		//----------------------------------------4----------------------------------------
		//отправка сообщений sendto

		char buf[50] = "Hello from Client 000"; // буфер ввода
		string bufStr;
		int libuf = 0;                          // количество отправленных байт
		int lobuf = 0;                          // количество прин€тых байт

		for (int i = 0; i < countMsg; i++) {
			if ((libuf = send(cC, buf, sizeof(buf), NULL)) == SOCKET_ERROR)
				throw TCPConnection::Helper::SetErrorMsgText("send:", WSAGetLastError());

			cout << " оличество отправленый байт: " << libuf << endl;
			cout << "“екст сообшени€: " << buf << endl << endl;

			//---------------------------------------- 5 ----------------------------------------
			if ((lobuf = recv(cC, buf, sizeof(buf), NULL)) == SOCKET_ERROR)
				throw TCPConnection::Helper::SetErrorMsgText("recv:", WSAGetLastError());

			cout << " оличество полученых байт сообщени€: " << lobuf << endl;
			cout << "“екст сообшени€: " << buf << endl << endl;

			bufStr = (string)buf;
			prepareString(bufStr, i + 1);
			strcpy(buf, bufStr.c_str());
		}
		
		//----------------------------------------6----------------------------------------
		//закрытие сокета и завершени€ работы с библиотекой WS2_32.DLL
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

void prepareString(string& str, int i)
{
	str.erase(18);
	if (i < 10)
	{
		str.append("00");
		str.append(to_string(i));
	}
	else if (i < 100)
	{
		str.append("0");
		str.append(to_string(i));
	}
	else
		str.append(to_string(i));
}
