#include "stdafx.h"
#include "TCPConnection.h"
#include <iostream>

using namespace TCPConnection;

std::string Helper::getErrorMessage(int code) {
	std::string message;
	switch (code) {
	case WSAEINTR: message = "������ ������� ��������"; break;
	case WSAEACCES: message = "���������� ����������"; break;
	case WSAEINVAL: message = "������ � ���������"; break;
	case WSAEMFILE: message = "������� ����� ������ �������"; break;
	case WSAEWOULDBLOCK: message = "������ �������� ����������"; break;
	case WSAEINPROGRESS: message = "�������� � �������� ��������"; break;
	case WSAEALREADY: message = "�������� ��� �����������"; break;
	case WSAENOTSOCK: message = "����� ����� �����������"; break;
	case WSAEDESTADDRREQ: message = "��������� ����� ������������"; break;
	case WSAEMSGSIZE: message = "��������� ������� �������"; break;
	case WSAEPROTOTYPE: message = "������������ ��� ��������� ��� ������"; break;
	case WSAENOPROTOOPT: message = "������ � ����� ���������"; break;
	case WSAEPROTONOSUPPORT: message = "�������� �� ��������������"; break;
	case WSAESOCKTNOSUPPORT: message = "��� ������ �� ��������������"; break;
	case WSAEOPNOTSUPP: message = "�������� �� ��������������"; break;
	case WSAEPFNOSUPPORT: message = "��� ���������� �� ��������������"; break;
	case WSAEAFNOSUPPORT: message = "��� ������� �� �������������� ����������"; break;
	case WSAEADDRINUSE: message = "����� ��� ������������"; break;
	case WSAEADDRNOTAVAIL: message = "����������� ����� �� ����� ���� �����������"; break;
	case WSAENETDOWN: message = "���� ���������"; break;
	case WSAENETUNREACH: message = "���� �� ���������"; break;
	case WSAENETRESET: message = "���� ��������� ����������"; break;
	case WSAECONNABORTED: message = "����������� ����� �����"; break;
	case WSAECONNRESET: message = "����� �������������"; break;
	case WSAENOBUFS: message = "�� ������� ������ ��� �������"; break;
	case WSAEISCONN: message = "����� ��� ���������"; break;
	case WSAENOTCONN: message = "����� �� ���������"; break;
	case WSAESHUTDOWN: message = "������ ���������"; break;
	case WSAETIMEDOUT: message = "���������� ���������� ��������  �������"; 	break;
	case WSAECONNREFUSED: message = "���������� ���������"; break;
	case WSAEHOSTDOWN: message = "���� � ����������������� ���������"; break;
	case WSAEHOSTUNREACH: message = "��� �������� ��� �����"; break;
	case WSAEPROCLIM: message = "������� ����� ���������"; break;
	case WSASYSNOTREADY: message = "���� �� ��������"; break;
	case WSAVERNOTSUPPORTED: message = "������ ������ ����������"; break;
	case WSANOTINITIALISED: message = "�� ��������� ������������� WS2_32.DLL"; break;
	case WSAEDISCON: message = "����������� ����������"; break;
	case WSATYPE_NOT_FOUND: message = "����� �� ������"; break;
	case WSAHOST_NOT_FOUND: message = "���� �� ������"; break;
	case WSATRY_AGAIN: message = "������������������ ���� �� ������"; break;
	case WSANO_RECOVERY: message = "��������������  ������"; break;
	case WSANO_DATA: message = "��� ������ ������������ ����"; break;
	case WSA_INVALID_HANDLE: message = "��������� ���������� �������  � �������"; break;
	case WSA_INVALID_PARAMETER: message = "���� ��� ����� ���������� � �������"; break;
	case WSA_IO_INCOMPLETE: message = "������ �����-������ �� � ���������� ���������"; break;
	case WSA_IO_PENDING: message = "�������� ���������� �����"; break;
	case WSA_NOT_ENOUGH_MEMORY: message = "�� ���������� ������"; break;
	case WSA_OPERATION_ABORTED: message = "�������� ����������"; break;
	case WSASYSCALLFAILURE: message = "��������� ���������� ���������� ������"; break;
	default: message = "����������� ������"; break;
	}
	return message;
}

void Helper::showErrorMessage(int code) {
	std::cout << std::endl << "-----" << "��� ������: " << code << std::endl << Helper::getErrorMessage(code) << std::endl << "-----" << std::endl;
}

std::string Helper::SetErrorMsgText(std::string Msg, int code) {
	return Msg + Helper::getErrorMessage(code);
};