#include <winsock2.h>
#pragma comment(lib, "WS2_32.lib") 

#include <string>

namespace TCPConnection {

	static class Helper {
	public:
		static std::string getErrorMessage(int code);
		static void showErrorMessage(int code);
		static std::string SetErrorMsgText(std::string Msg, int code);
	};

}