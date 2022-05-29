#pragma once
#include "core.h"

#ifdef _WIN32
#include <Windows.h>
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
		sockaddr_in* in;
		wsocket()
		{
			s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
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

	class client
	{
	public:
		client()
		{

		}
	};

	class server
	{
	private:
		wsocket web_sock;
	public:
		server()
		{

		}

		void wait()
		{
			listen(web_sock.s, 0);
		}

		void accept_req()
		{
			int p = 4;
			accept(web_sock.s, (sockaddr*)web_sock.in, &p);
		}
	};

	typedef unsigned char ipv4[4];
	typedef unsigned char ipv6[16];

	void make_ipv4(std::string str, ipv4 _ip)
	{
		int c = 0, d = 0;
		while (str[c] != '\0')
		{
			if (str[c] == '.')
				d++;
			if(str[c] >= 'a')
				_ip[d] = _ip[d] * 16 + str[c] - 'a';
			else
				_ip[d] = _ip[d] * 16 + str[c] - 'a';
			c++;
		}
	}

	template<typename T>
	class pack_header
	{
	public:
		pack_header() {}
		T info;
		uint32_t size = 0;
	};

	template<typename T>
	class package
	{
	public:
		io::pack_header<T> head;
		std::vector<uint8_t> body; // buffer ?
		package() {}
		size_t size()
		{
			return sizeof(head.info) + body.size();
		}
	};

	class basic_package
	{
	public:
		io::pack_header<std::string> head;
		io::buffer body;
		basic_package() {}
		size_t size()
		{
			return head.info.size() + body.size();
		}
		void send_to(wsocket sock, io::ipv4 _ip)
		{
			send(sock.s, body.c_str(), body.size(), 0);
		}
	};
}