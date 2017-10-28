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
		//������������� WS2_32.DLL
		if (WSAStartup(MAKEWORD(2, 0), &wsa) != 0)
			throw TCPConnection::Helper::SetErrorMsgText("Startup: ", WSAGetLastError());

		//----------------------------------------2----------------------------------------
		//�������� ������ � ��������� ��� ����������. ����� ����� �������������� ��� ����������
		//(�����, ��������������� �� �����)
		if ((sS = socket(AF_INET, SOCK_STREAM, NULL)) == INVALID_SOCKET)
			throw TCPConnection::Helper::SetErrorMsgText("Socket: ", WSAGetLastError());

		SOCKADDR_IN serv;
		serv.sin_family = AF_INET; //������������ IP-���������
		serv.sin_addr.s_addr = INADDR_ANY; //����� ����������� IP-�����
		serv.sin_port = htons(2000); //����

		//��� ��������� ���������� ������ ������������ ������� bind.
		//��� ���� �������, ��� ����� ��������� � �����������.
		if (bind(sS, (LPSOCKADDR)&serv, sizeof(serv)) == SOCKET_ERROR)
			throw TCPConnection::Helper::SetErrorMsgText("Bind: ", WSAGetLastError());

		//----------------------------------------3----------------------------------------
		//listen ��������� �����, ��������������� �� �����, � ��������� �������������(��������� ������ � ������)
		//� ������ ��������� ��������� ������� ����������.
		if (listen(sS, SOMAXCONN) == SOCKET_ERROR)
			throw TCPConnection::Helper::SetErrorMsgText("Listen: ", WSAGetLastError());

		SOCKET cS; //�����, ��������������� ��� ������ ������� � ��������
		SOCKADDR_IN clnt;
		memset(&clnt, 0, sizeof(clnt));
		int lclnt = sizeof(clnt);

		cout << "[1] - �������� ������� " << endl;
		cout << "[2] - ����� " << endl;
		cin >> action;
		//accept ��������� ������� ������� � ��������� �������� �� �������, ���� ��������� ������� �� ��������
		//������� connect(���������� ����������)
		while (action == "1") {
			if ((cS = accept(sS, (sockaddr*)&clnt, &lclnt)) == INVALID_SOCKET)
				throw TCPConnection::Helper::SetErrorMsgText("Accept: ", WSAGetLastError());

			//----------------------------------------4----------------------------------------
			//����� �������
			char bfrom[50]; // ����� �����
			int lobuf = 0;  // ���������� �������� ����
			int libuf = 0;  // ���������� ������������ ����
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
			cout << "[1] - �������� ������� " << endl;
			cout << "[2] - ����� " << endl;
			cin >> action;
			system("cls");
		}
		//----------------------------------------6----------------------------------------
		//�������� ������ � ���������� ������ � ����������� WS2_32.DLL
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