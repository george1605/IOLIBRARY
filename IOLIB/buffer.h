#pragma once
#include "core.h"
#include <memory>
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
		size_t Size = 0;
	public:
		buffer()
		{
			p = (char*)malloc(10);
			Size = 10;
		}
		buffer(std::string n)
		{
			this->p = (char*)n.c_str();
			this->Size = n.size();
		}
		buffer(char* x)
		{
			if (x == nullptr)
				this->Size = 0;
			else 
				this->Size = strlen(x);
			this->p = x;

		}
		buffer(int size)
		{
			if (size >= BUFLIMIT)
			{
				p = (char*)malloc(BUFLIMIT); // reosrts to the basic buffer
				Size = BUFLIMIT;
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
		io::expect<char> operator [](int pos)
		{
			if (pos < 0 || pos > Size) // out of bounds
				return io::expect<char>(io::exception(ENULLPTR));
			return io::expect<char>(p[pos]);
		}
                char at(unsigned x)
                {
                        return ptr[x % Size];
                }
                void set(unsigned pos, char x)
                {
                        ptr[pos % Size] = x;
                }
	};

        class list_buffer : llist {};

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

        class smart_buffer : unique_ptr<char> 
        {
        public:
            smart_buffer() : unique_ptr(new char(10)){}
            smart_buffer(size_t size) : unique_ptr(new char(size)){}
            
        };

	void* os_alloc(int size, int type)
	{
#ifdef __linux__
		void* k = sbrk(0);
		brk(k + size + 1);
		return k;
#endif

#ifdef _WIN32
		return nullptr;
#endif
	}
}
