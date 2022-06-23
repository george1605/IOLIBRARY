#pragma once
#include <iostream>
// is system portable 

namespace io
{
#ifndef BADACCESS
#define EBADACCESS 0x7FF
#endif
#define MEM_READ (1 << 1)
#define MEM_WRITE (1 << 2)
#define MEM_LOCKED (1 << 3)
	class memarea
	{
	private:
		char* addr;
		int flags;
		size_t cnt = 0, Size = 0;
	public:
		memarea() {}
		memarea(size_t size)
		{
			Size = size;
			addr = (char*)malloc(size);
		}
		void unlock()
		{
			flags &= ~MEM_LOCKED;
		}

		void lock()
		{
			flags |= MEM_LOCKED;
		}

		char read()
		{
			if ((flags & MEM_LOCKED) || (cnt >= Size))
				return (char)-1;
			if (flags & MEM_READ)
				return addr[cnt++];
		}

		void clear()
		{
			this->cnt = 0;
			memset(addr, 0, Size); // or ZeroMemory ?
		}
	};

	template<typename T>
	void bit_trans(T& s1, T& s2)
	{
		memmove(&s1, &s2, sizeof(T));
	}

	class io_context
	{
	public:
		io_context() {}
		void run() {}

	};

	class err_info
	{
	public:
		int code;
		err_info(int n)
		{
			code = n;
		}
		void print()
		{
			if (code == EBADACCESS)
				std::cout << "Error: EBADACCESS";
			else
				std::cout << "Error: EUNKNOWN";
		}
	};
}