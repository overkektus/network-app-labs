#include <string>
#include <iostream>
#include "conio.h"
#include "TCPConnection.h"
#pragma warning (disable : 4996)

using namespace std;

int main() {
	setlocale(LC_CTYPE, "rus");

	WSADATA wsa;
	SOCKET sS;
	string action;

	try {
		//----------------------------------------1----------------------------------------
		//Инициализация WS2_32.DLL
		if (WSAStartup(MAKEWORD(2, 0), &wsa) != 0)
			throw TCPConnection::Helper::SetErrorMsgText("Startup: ", WSAGetLastError());

		//----------------------------------------2----------------------------------------
		//создание сокета и установка его параметров. сокет будет использоваться для соединения
		//(сокет, ориентированный на поток)
		if ((sS = socket(AF_INET, SOCK_STREAM, NULL)) == INVALID_SOCKET)
			throw TCPConnection::Helper::SetErrorMsgText("Socket: ", WSAGetLastError());

		SOCKADDR_IN serv;
		serv.sin_family = AF_INET; //используется IP-адресация
		serv.sin_addr.s_addr = INADDR_ANY; //любой собственный IP-адрес
		serv.sin_port = htons(2000); //порт

		//Для установки параметров сокета используется функция bind.
		//При этом говорят, что сокет связывают с параметрами.
		if (bind(sS, (LPSOCKADDR)&serv, sizeof(serv)) == SOCKET_ERROR)
			throw TCPConnection::Helper::SetErrorMsgText("Bind: ", WSAGetLastError());

		//----------------------------------------3----------------------------------------
		//listen переводит сокет, ориентированный на поток, в состояния прослушивания(открывает доступ к сокету)
		//и задает некоторые параметры очереди соединений.
		if (listen(sS, SOMAXCONN) == SOCKET_ERROR)
			throw TCPConnection::Helper::SetErrorMsgText("Listen: ", WSAGetLastError());

		SOCKET cS; //сокет, предназначенный для обмена данными с клиентом
		SOCKADDR_IN clnt;
		memset(&clnt, 0, sizeof(clnt));
		int lclnt = sizeof(clnt);

		cout << "[1] - ожидание клиента " << endl;
		cout << "[2] - выход " << endl;
		cin >> action;
		//accept переводит процесс сервера в состояние ожидания до момента, пока программа клиента не выполнит
		//функцию connect(установить соединение)
		while (action == "1") {
			if ((cS = accept(sS, (sockaddr*)&clnt, &lclnt)) == INVALID_SOCKET)
				throw TCPConnection::Helper::SetErrorMsgText("Accept: ", WSAGetLastError());

			//----------------------------------------4----------------------------------------
			//Обмен данными
			char bfrom[50]; // буфер ввода
			int lobuf = 0;  // количество принятых байт
			int libuf = 0;  // количество отправленных байт
			cout << endl;
			cout << "IP: " << inet_ntoa(clnt.sin_addr) << endl;
			cout << "Port: " << ntohs(clnt.sin_port) << endl << endl;

			do {
				if ((lobuf = recv(cS, bfrom, sizeof(bfrom), NULL)) == SOCKET_ERROR)
					throw TCPConnection::Helper::SetErrorMsgText("recv:", WSAGetLastError());

				//---------------------------------------- 5 ----------------------------------------
				if ((libuf = send(cS, bfrom, sizeof(bfrom), NULL)) == SOCKET_ERROR)
					throw TCPConnection::Helper::SetErrorMsgText("send:", WSAGetLastError());

			} while (lobuf != 0);

			cout << endl;
			cout << "[1] - ожидание клиента " << endl;
			cout << "[2] - выход " << endl;
			cin >> action;
			system("cls");
		}
		//----------------------------------------6----------------------------------------
		//закрытие сокета и завершения работы с библиотекой WS2_32.DLL
		if (closesocket(sS) == SOCKET_ERROR)
			throw TCPConnection::Helper::SetErrorMsgText("Closesocket: ", WSAGetLastError());
		if (WSACleanup() == SOCKET_ERROR)
			throw TCPConnection::Helper::SetErrorMsgText("Cleanup: ", WSAGetLastError());
	}
	catch (string errorMsg) {
		cout << endl << errorMsg;
	}

	return 0;
}