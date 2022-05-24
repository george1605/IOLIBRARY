#pragma once
#include "core.h"
#ifdef _MSC_VRT
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifdef __linux__
#include <unistd.h>
#endif

#if defined(__ARM__) || defined(__AVR__)
#define BUFLIMIT 0x10000
#else
#define BUFLIMIT sizeof(long long) * 1024 * 1024
#endif

namespace io
{
#define HEAP_ALLOC 1
#define STACK_ALLOC 2
	class buffer
	{
	protected:
		char* p;
		int Size = 0;
	public:
		buffer()
		{
			p = (char*)malloc(10);
			Size = 10;
		}
		buffer(int size)
		{
			if (size >= BUFLIMIT)
			{
				p = (char*)malloc(10); // reosrts to the basic buffer
				Size = 10;
				io::error = EBIGBUF;
			}
			else
			{
				p = (char*)malloc(size);
			}
		}
		~buffer()
		{
			Size = 0;
			if(p)
				free(p);
		}
		void cpy(char* x)
		{
			memcpy(p, x, strlen(x));
		}
		void scpy(char* x)
		{
			int c = 0;
			while (x[c] && p[c])
				p[c] = x[c], c++;
		}
		char* c_str()
		{
			return p;
		}
		int size()
		{
			return Size;
		}
		char operator [](int pos)
		{
			if (pos < 0 || pos > Size) // out of bounds
				return '\0';
			return p[pos];
		}
	};

	class lock_buffer : public buffer
	{
	private:
		bool locked;
	public:
		lock_buffer() : buffer(), locked(false)
		{

		}
		bool active()
		{
			return locked;
		}
		void lock()
		{
			if (locked)
				return;
			locked = true;
		}
		void unlock()
		{
			locked = false;
		}
	};

	void* os_alloc(int size, int type)
	{
#ifdef __linux__
		void* k = sbrk(0);
		brk(k + size + 1);
		return k;
#endif

#ifdef _WIN32
		return NULL;
#endif
	}
}