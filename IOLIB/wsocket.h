#pragma once
#include "core.h"

#ifdef _WIN32
#include <winsock.h>
#include <WinSock2.h>
#endif

#ifdef __linux__
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#endif

namespace io
{
	enum wproto
	{
		TCP = 0,
		UDP = 1
	};

	class wsocket
	{
	public:
#ifdef _WIN32
		SOCKET s;
		sockaddr_in in;
		wsocket()
		{
			socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		}
#endif
	};

	class sock_info
	{
	private:
		int sock_type;
	public:
		sock_info()
		{
#ifdef _WIN32
			sock_type = AF_INET;

#endif

		}
	};

	void connect()
	{

	}

}