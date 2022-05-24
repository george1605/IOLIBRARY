#pragma once
#include "core.h"

namespace io
{

	class wsocket
	{

	};

	class sock_info
	{
	private:
		int sock_type;
	public:
		sock_info()
		{
#ifdef _WIN32
#include <WinSock2.h>
			sock_type = AF_INET;

#endif

		}
	};

	void connect()
	{

	}

}