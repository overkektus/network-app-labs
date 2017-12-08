// Mailslot.cpp : Defines the entry point for the console application.
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

	HANDLE sH;
	DWORD rb;
	char buf[26];
	double start, end;

	try {
		HANDLE hMS;
		double start, end;

		while (true) {
			int i = 0;

			if ((hMS = CreateMailslot(L"\\\\.\\mailslot\\Box", 300, MAILSLOT_WAIT_FOREVER, NULL)) == INVALID_HANDLE_VALUE)
				throw "Error: CreateMailslot";

			char rbuf[50];
			DWORD rms;

			do {
				i++;

				if (!ReadFile(hMS, rbuf, sizeof(rbuf), &rms, NULL))
					throw "Error: ReadFile";

				if (i == 1)
					start = clock();

				cout << rbuf << endl;
			} while (strcmp(rbuf, " ") != 0);

			end = clock();

			cout << "Время передачи: " << (end - start) / 1000 << " сек." << endl;
			cout << "Количество сообщений: " << i - 1 << endl << endl;

			if (!CloseHandle(hMS))
				throw "Error: CloseHandle";
		}
	}
	catch (string errorMessage) {
		cout << errorMessage << endl;
	}
	_getch();

    return 0;
}

