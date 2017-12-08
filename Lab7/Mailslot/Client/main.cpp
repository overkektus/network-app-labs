// Client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "time.h"
#include <iostream>
#include <Windows.h>
#include <string>
#include <conio.h>

using namespace std;

int main() {

	setlocale(0, "");

	HANDLE cH;
	char wbuf[26] = "Hello from Maislot-client";
	DWORD lBuf;
	double start, end;
	int count;

	try {
		
		if ((cH = CreateFile(L"\\\\DESKTOP-EV1DP4P\\mailslot\\Box",
			GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL,
			OPEN_EXISTING,
			NULL, NULL)) == INVALID_HANDLE_VALUE)
			throw "CreateFile exception";


		cout << "Введите кол-во сообщений: ";
		cin >> count;

		start = clock();

		for (int i = 0; i < count; i++) {
			char q[6];
			sprintf_s(q, "%d", i + 1);
			char buf[sizeof(wbuf) + sizeof(q)];
			strcpy_s(buf, wbuf);
			strcat_s(buf, q);

			if (!WriteFile(cH, buf, sizeof(buf), &lBuf, NULL))
				throw "WriteFile exception";

			cout << "Message " << i + 1 << endl;
		}

		end = clock();

		if (!WriteFile(cH, " ", sizeof(" "), &lBuf, NULL))
			throw "WriteFile exception";
		
		if(!CloseHandle(cH))
			throw "Error: CloseHandle";

		cout << endl << "Время передачи: " << (end - start) / 1000 << " сек." << endl << endl;
	}
	catch (string errorMessage) {
		cout << errorMessage << endl;
	}
	_getch();
    return 0;
}

