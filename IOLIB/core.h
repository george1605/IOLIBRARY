#pragma once
#include <stdlib.h>
#include <vector>
#include <initializer_list>
#include <string.h>
#if _MSC_VER > 0
#define _CRT_SECURE_NO_WARNINGS 1
#endif

#ifdef __GNUC__
#define asm __asm__
#endif

#ifdef __cplusplus

namespace io
{

#endif

#define __DENIED static
#define __UNSAFE private: \

#define EBIGBUF 0xA00
#define ESOCKERR 0xA01
#define ENOFILE 0xA02
	int error = 0;

	void printc(char x)
	{
		printf("%c", x);
	}

	void printw(wchar_t w)
	{
		wprintf(L"%c", w);
	}

	const char* perror(int x)
	{
		if (x == EBIGBUF)
			return "EBIGBUF";
		else if (x == ESOCKERR)
			return "ESOCKERR";
		else if (x == ENOFILE)
			return "ENOFILE";
		return NULL;
	}

	int get_rand(int seed = 1)
	{
		long x = 353262524;
		long y = 746843423;
		return (x << seed | y) ^ 5;
	}

	int get_srand(int seed = 1)
	{
		return ((get_rand(seed) << 1) % 1000);
	}

	void print_err()
	{
		printf("Error %s", io::perror(io::error));
	}

	template<typename T>
	class queue
	{
	private:
		T* ptr;
		int Size = 0, Cap;
	public:
		queue()
		{
			ptr = (T*)malloc(sizeof(T) * 5);
			Cap = 5;
		}
		queue(std::vector<T> vec)
		{
			Size = vec.size();
			Cap = Size + 5;
			ptr = (T*)malloc(sizeof(T) * Cap);
			for (int i = 0; i < Size; i++)
				ptr[i] = vec[i];
		}
		queue(std::initializer_list<T> list)
		{
			Size = list.size();
			Cap = Size + 5;
			ptr = (T*)malloc(sizeof(T) * Cap);
		}
		~queue()
		{
			if (ptr)
				free(ptr);
		}
		void resize(int x)
		{
			realloc(ptr, x);
			Cap = x;
		}
		void push(T value)
		{
			if (Size >= Cap)
				resize(Size + 5);

			ptr[Size++] = value;
		}
		void pop()
		{
			if (Size >= 1)
				return;
			ptr[Size--] = 0;
		}
		int size()
		{
			return Size;
		}
	};

	class llink
	{
	public:
		llink* next = NULL;
		llink* prev = NULL;

		long value;
		llink() {}
		llink(int a) { value = a; }
		~llink()
		{
			llink* p;
			if (this->next == NULL)
				return;
			for (p = this->next->next; p != NULL; p = p->next);
		}
		void alloc(int x)
		{
			llink* p;
			this->next = new llink;
			p = this->next;
			for (int a = 1; a < x; a++)
			{
				p->next = new llink(a);
				p->next->prev = p;
				p = p->next;
			}
		}
		llink* begin()
		{
			llink* q;
			for (q = this->prev; q->prev != NULL; q = q->prev);
			return q;
		}
		llink* end()
		{
			llink* q;
			for (q = this->next; q->next != NULL; q = q->next);
			return q;
		}
		void show()
		{
			llink* p = this->next;
			while (p != NULL)
			{
				printf("%i ",p->value);
				p = p->next;
			}
		}
		void add()
		{
			llink* x = end();
			x->next = new llink;
		}
		long operator [](int x)
		{
			int c = 0;
			llink* q;
			for (q = this->next; q->next != NULL && c < x; q = q->next)
				c++;
			return q->value;
		}
		bool empty()
		{
			return (this->prev == NULL && this->next == NULL);
		}
		__UNSAFE void unlink() // unsafe functions are private
		{
			this->next = NULL;
			this->prev = NULL;
		}
	};
	typedef void* handle;

	handle open_hnd(char* fname, char* mode)
	{
#include <winbase.h>
		return NULL;
		
	}


	void simple_wait(int j = 10000)
	{
		for (int i = 0; i < j; i++);
	}

	void pause()
	{
#ifdef _MSC_VRT
		system("pause");
		return;
#endif

		getc(stdin);
	}

	template<typename T>
	class smart_ptr
	{

	};

	template<typename T, typename X>
	struct pair
	{
		T first;
		X second;
		pair() : first((T)0), second((X)0) {}
		pair(T n, X m) : first(n), second(m) {}
		void copy_to(void* ptr) // to list
		{
			*(T*)ptr = first;
			*(X*)(ptr + sizeof(T)) = second;
		}
	};

	typedef unsigned char* uuid;
	bool gen_uuid(uuid _id)
	{
		if (_id == NULL) return false;
		int a;
		for (a = 0; a < 16 && _id[a] != NULL; a++)
			_id[a] = rand() % 256, srand(a << (a % 4 + 1));
		return true;
	}

	void printh(unsigned char* buffer)
	{
		int a;
		for (a = 0; buffer[a] != NULL; a++)
			printf("%02x ", buffer[a]);
	}

	void printu(uuid buffer)
	{
		int a;
		for (a = 0; buffer[a] != NULL && a < 16; a++)
			printf("%02x ", buffer[a]);
	}

	uuid new_uuid()
	{
		return (uuid)malloc(16);
	}

	void free_uuid(uuid x)
	{
		free(x);
	}

	wchar_t* unicode(char* buf)
	{
		if (buf == NULL)
			return (wchar_t*)NULL;
		wchar_t* ptr = new wchar_t[strlen(buf)];
		mbstowcs(ptr, buf, strlen(buf));
	}
#ifndef PAGE_SIZE
	#define PAGE_SIZE 4096
#endif
	void alloc_pages(int n, void* arr[])
	{
		for (int a = 0; a < n && arr[a] != 0; a++)
			arr[a] = malloc(PAGE_SIZE);
	}

	void free_pages(void* arr[])
	{
		for (int a = 0; arr[a] != 0; a++)
			free(arr[a]);
	}

	typedef struct
	{
		char value : 1;
	} tbool;

#ifdef __cplusplus

	class blockdev
	{
	private:
		char* mapped;
		char* fname;
		int port;
	public:
		blockdev() { port = 0xa0; }
		void write()
		{
			if (fname != NULL) // vfs
			{
				fopen(fname, "w");
			}
		}
	};
}

#endif