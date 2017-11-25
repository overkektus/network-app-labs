#include "stdafx.h"
#include "TCPConnection.h"
#include <iostream>

using namespace TCPConnection;

std::string Helper::getErrorMessage(int code) {
	std::string message;
	switch (code) {
	case WSAEINTR: message = "Работа функции прервана"; break;
	case WSAEACCES: message = "Разрешение отвергнуто"; break;
	case WSAEINVAL: message = "Ошибка в аргументе"; break;
	case WSAEMFILE: message = "Слишком много файлов открыто"; break;
	case WSAEWOULDBLOCK: message = "Ресурс временно недоступен"; break;
	case WSAEINPROGRESS: message = "Операция в процессе развития"; break;
	case WSAEALREADY: message = "Операция уже выполняется"; break;
	case WSAENOTSOCK: message = "Сокет задан неправильно"; break;
	case WSAEDESTADDRREQ: message = "Требуется адрес расположения"; break;
	case WSAEMSGSIZE: message = "Сообщение слишком длинное"; break;
	case WSAEPROTOTYPE: message = "Неправильный тип протокола для сокета"; break;
	case WSAENOPROTOOPT: message = "Ошибка в опции протокола"; break;
	case WSAEPROTONOSUPPORT: message = "Протокол не поддерживается"; break;
	case WSAESOCKTNOSUPPORT: message = "Тип сокета не поддерживается"; break;
	case WSAEOPNOTSUPP: message = "Операция не поддерживается"; break;
	case WSAEPFNOSUPPORT: message = "Тип протоколов не поддерживается"; break;
	case WSAEAFNOSUPPORT: message = "Тип адресов не поддерживается протоколом"; break;
	case WSAEADDRINUSE: message = "Адрес уже используется"; break;
	case WSAEADDRNOTAVAIL: message = "Запрошенный адрес не может быть использован"; break;
	case WSAENETDOWN: message = "Сеть отключена"; break;
	case WSAENETUNREACH: message = "Сеть не достижима"; break;
	case WSAENETRESET: message = "Сеть разорвала соединение"; break;
	case WSAECONNABORTED: message = "Программный отказ связи"; break;
	case WSAECONNRESET: message = "Связь восстановлена"; break;
	case WSAENOBUFS: message = "Не хватает памяти для буферов"; break;
	case WSAEISCONN: message = "Сокет уже подключен"; break;
	case WSAENOTCONN: message = "Сокет не подключен"; break;
	case WSAESHUTDOWN: message = "Нельзя выполнить"; break;
	case WSAETIMEDOUT: message = "Закончился отведенный интервал  времени"; 	break;
	case WSAECONNREFUSED: message = "Соединение отклонено"; break;
	case WSAEHOSTDOWN: message = "Хост в неработоспособном состоянии"; break;
	case WSAEHOSTUNREACH: message = "Нет маршрута для хоста"; break;
	case WSAEPROCLIM: message = "Слишком много процессов"; break;
	case WSASYSNOTREADY: message = "Сеть не доступна"; break;
	case WSAVERNOTSUPPORTED: message = "Данная версия недоступна"; break;
	case WSANOTINITIALISED: message = "Не выполнена инициализация WS2_32.DLL"; break;
	case WSAEDISCON: message = "Выполняется отключение"; break;
	case WSATYPE_NOT_FOUND: message = "Класс не найден"; break;
	case WSAHOST_NOT_FOUND: message = "Хост не найден"; break;
	case WSATRY_AGAIN: message = "Неавторизированный хост не найден"; break;
	case WSANO_RECOVERY: message = "Неопределенная  ошибка"; break;
	case WSANO_DATA: message = "Нет записи запрошенного типа"; break;
	case WSA_INVALID_HANDLE: message = "Указанный дескриптор события  с ошибкой"; break;
	case WSA_INVALID_PARAMETER: message = "Один или более параметров с ошибкой"; break;
	case WSA_IO_INCOMPLETE: message = "Объект ввода-вывода не в сигнальном состоянии"; break;
	case WSA_IO_PENDING: message = "Операция завершится позже"; break;
	case WSA_NOT_ENOUGH_MEMORY: message = "Не достаточно памяти"; break;
	case WSA_OPERATION_ABORTED: message = "Операция отвергнута"; break;
	case WSASYSCALLFAILURE: message = "Аварийное завершение системного вызова"; break;
	default: message = "Неизвестная ошибка"; break;
	}
	return message;
}

void Helper::showErrorMessage(int code) {
	std::cout << std::endl << "-----" << "Код ошибки: " << code << std::endl << Helper::getErrorMessage(code) << std::endl << "-----" << std::endl;
}

std::string Helper::SetErrorMsgText(std::string Msg, int code) {
	return Msg + Helper::getErrorMessage(code);
};