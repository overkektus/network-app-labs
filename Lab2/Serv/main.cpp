#include <string>
#include <iostream>
#include "conio.h"
#include "TCPConnection.h"

using namespace std;


int main()
{
	setlocale(LC_CTYPE, "rus");

	WSADATA wsa;
	SOCKET sS;

	try {
		//Открытие библиотеки
		if (WSAStartup(MAKEWORD(2, 0), &wsa) != 0)
			throw TCPConnection::Helper::SetErrorMsgText("Startup: ", WSAGetLastError());

		if ((sS = socket(AF_INET, SOCK_STREAM, NULL)) == INVALID_SOCKET)
			throw TCPConnection::Helper::SetErrorMsgText("Socket: ", WSAGetLastError());

		SOCKADDR_IN serv;
		serv.sin_family = AF_INET;
		serv.sin_addr.s_addr = INADDR_ANY;
		serv.sin_port = htons(2000);

		if (bind(sS, (LPSOCKADDR)&serv, sizeof(serv)) == SOCKET_ERROR)
			throw TCPConnection::Helper::SetErrorMsgText("Bind: ", WSAGetLastError());

		if (listen(sS, SOMAXCONN) == SOCKET_ERROR)
			throw TCPConnection::Helper::SetErrorMsgText("Listen: ", WSAGetLastError());


		SOCKET cS;
		SOCKADDR_IN clnt;
		memset(&clnt, 0, sizeof(clnt));
		int lclnt = sizeof(clnt);

		if ((cS = accept(sS, (sockaddr*)&clnt, &lclnt)) == INVALID_SOCKET)
			throw TCPConnection::Helper::SetErrorMsgText("Accept: ", WSAGetLastError());


		printf_s("Connect from: %u.%u.%u.%u:%u\n", 
			(unsigned char)clnt.sin_addr.S_un.S_un_b.s_b1,
			(unsigned char)clnt.sin_addr.S_un.S_un_b.s_b2,
			(unsigned char)clnt.sin_addr.S_un.S_un_b.s_b3,
			(unsigned char)clnt.sin_addr.S_un.S_un_b.s_b4,
			ntohs(clnt.sin_port));

		char ibuf[50],
			obuf[50] = "sever: принято ";
		int libuf = 0,
			lobuf = 0;

		for (int i = 0; i < 1000; i++) {
			if ((libuf = recv(cS, ibuf, sizeof(ibuf), NULL)) == SOCKET_ERROR)
				throw TCPConnection::Helper::SetErrorMsgText("Recv:", WSAGetLastError());

			cout << "Message from client: " << ibuf << endl;
			//memset(ibuf, 0, sizeof(ibuf));
		}


		//Закрытие библиотеки
		if (closesocket(sS) == SOCKET_ERROR)
			throw TCPConnection::Helper::SetErrorMsgText("Closesocket: ", WSAGetLastError());
		if (WSACleanup() == SOCKET_ERROR)
			throw TCPConnection::Helper::SetErrorMsgText("Cleanup: ", WSAGetLastError());
	}
	catch (string errorMsg) {
		cout << endl << errorMsg;
	}

	_getch();
	return 0;
}