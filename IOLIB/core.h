#pragma once
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <initializer_list>
#include <string.h>
#if _MSC_VER > 0
#include <Windows.h>
#define _CRT_SECURE_NO_WARNINGS 1
#endif

#ifdef __GNUC__
#define asm __asm__
#endif

namespace io
{

#define __DENIED static
#define __UNSAFE private: \
// general errors - (eg. no library) -
#define ENOX11 0x100
#define ENOGL 0x200
// run-time errors 
#define ENULLPTR 0x700
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

	void prints(const char* s)
	{
		printf("%s", s);
	}

	const char* perror(int x)
	{
		if (x == EBIGBUF)
			return "EBIGBUF";
		else if (x == ESOCKERR)
			return "ESOCKERR";
		else if (x == ENOFILE)
			return "ENOFILE";
		else if (x == ENOX11)
			return "ENOX11";
		return nullptr;
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
	class string
	{
	private:
		char* ptr;
		int Size, Cnt = 0;
	public:
		string()
		{
			Size = 0;
		}
		string(size_t size)
		{
			ptr = (char*)malloc(size);
			Size = size;
		}
		string(size_t size, char x)
		{
			ptr = (char*)malloc(size);
			Size = size;
			memset(ptr, x, size);
		}
		string(const char* p)
		{
			ptr = (char*)p;
		}
		~string()
		{
			if (ptr)
				free(ptr);
			this->Size = 0;
		}
		bool empty()
		{
			return (ptr == nullptr);
		}
		void push(char c)
		{

		}
		size_t size()
		{
			return Size;
		}
		char* addr()
		{
			return this->ptr;
		}
		bool copy_from(io::string p)
		{
			if (p.empty())
				return false;
			memcpy(ptr, p.addr(), p.size());
			return true;
		}
		std::string to_std()
		{
			return std::string(ptr);
		}
		char operator [](int k)
		{
			if (k > Size)
				return 0;
			return ptr[k];
		}

		void operator =(const char* x)
		{
			this->ptr = (char*)x;
		}
	};

	void exec_syscall(size_t x, void* info)
	{
#ifdef __linux__
		syscall(x, info);
#elif defined(_WIN32)

#endif
	}

	std::ostream& operator << (std::ostream& o, io::string str)
	{
		if (str.addr() == nullptr)
			return o;
		o << str.addr();
		return o;
	}

	class exception
	{
	public:
		int code;
		io::string name; // for custom errors
		io::string body;
		exception(int code)
		{
			this->code = code;
			this->body = "Error";
		}
		exception(int code, io::string x)
		{
			this->code = code;
		}
		exception(io::string a, io::string b)
		{

		}
		void print()
		{
			if(code != 0)
				std::cout << io::perror(code) << ": " << this->body;
			else
				std::cout << io::perror(code) << ": " << this->body;
		}
		bool is_null()
		{
			return (name.empty() && body.empty());
		}
	};

	template<typename T>
	class expect
	{
	private:
		T val;
		io::exception err;
	public:
		expect()
		{
			err = io::exception(0);
		}
		expect(T n)
		{
			val = n;
		}
		expect(io::exception n)
		{
			err = n;
		}
		io::exception error()
		{
			return err;
		}
		T value()
		{
			return value;
		}
		void operator =(T x)
		{
			if (err.is_null())
				value = x;
		}
	};

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

	void exec_cmd(const char* x)
	{
#ifdef __linux__
		int fd = fork();
		execve(x, nullptr, nullptr);
#endif

#ifdef _WIN32
		ShellExecuteA(nullptr, "open", x, nullptr, nullptr, SW_NORMAL);
#endif
	}

	class llink
	{
	public:
		llink* next = nullptr;
		llink* prev = nullptr;

		long value = 0;
		llink() {}
		llink(int a) { value = a; }
		~llink()
		{
			llink* p;
			if (this->next == nullptr)
				return;
			for (p = this->next->next; p != nullptr; p = p->next);
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
			for (q = this->prev; q->prev != nullptr; q = q->prev);
			return q;
		}
		llink* end()
		{
			llink* q;
			for (q = this->next; q->next != nullptr; q = q->next);
			return q;
		}
		void show()
		{
			llink* p = this->next;
			while (p != nullptr)
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
			for (q = this->next; q->next != nullptr && c < x; q = q->next)
				c++;
			return q->value;
		}
		bool empty()
		{
			return (this->prev == nullptr && this->next == nullptr);
		}
		__UNSAFE void unlink() // unsafe functions are private
		{
			this->next = nullptr;
			this->prev = nullptr;
		}
	};

	class btree
	{
	private:
		btree* ch1, * ch2;
	public:
		long info;
		btree() {}
		~btree()
		{
			delete ch1;
			delete ch2;
		}
		void invert()
		{
			std::swap(ch1->info, ch2->info);
		}
		void add_node()
		{
			if (!ch2)
				ch1 = new btree;
			else
				ch2 = new btree;
		}
		void unlink()
		{
			this->ch1 = this->ch2 = nullptr;
		}
		int no_child()
		{
			return (ch1 != nullptr) + (ch2 != nullptr);
		}
	};

	void simple_wait(int j = 10000)
	{
		for (int i = 0; i < j; i++);
	}

	void pause()
	{
#ifdef _MSC_VER
		system("pause");
		return;
#endif

		getc(stdin);
	}

	template<typename T>
	class smart_ptr
	{
	protected:
		void* ptr = nullptr;
	public:
		smart_ptr()
		{}
		smart_ptr(size_t n)
		{
			ptr = malloc(n);
		}
		~smart_ptr()
		{
			if (ptr)
				free(ptr);
		}
		void resize(size_t k)
		{
			realloc(this->ptr, k);
		}
	};

	template<typename T, typename X>
	struct pair
	{
		T first;
		X second;
		pair() {}
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
		if (_id == nullptr) return false;
		int a;
		for (a = 0; a < 16 && _id[a] != '\0'; a++)
			_id[a] = rand() % 256, srand(a << (a % 4 + 1));
		return true;
	}

	void printh(unsigned char* buffer)
	{
		int a;
		for (a = 0; buffer[a] != '\0'; a++)
			printf("%02x ", buffer[a]);
	}

	void printu(uuid buffer)
	{
		int a;
		for (a = 0; buffer[a] != '\0' && a < 16; a++)
			printf("%02x ", buffer[a]);
	}

	uuid new_uuid()
	{
		uuid x = (uuid)malloc(16);
		if (x == nullptr) return x; 
		x[15] = 0;
		return x;
	}

	void free_uuid(uuid x)
	{
		free(x);
	}

	wchar_t* unicode(char* buf)
	{
		if (buf == nullptr)
			return (wchar_t*)nullptr;
		int x = strlen(buf);
		wchar_t* ptr = new wchar_t[x];
		mbstowcs(ptr, buf, x);
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

	struct tbool
	{
		char value : 1;
	};

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
			if (fname != nullptr) // vfs
			{
				fopen(fname, "w");
			}
		}
	};

#define FILE_HANDLE 1
#define BUFF_HANDLE 2
#define DEV_HANDLE 4
#define UUID_HANDLE 8

	template<typename T>
	class handle
	{
		T* ptr;
	public:
		handle()
		{
			ptr = (T*)malloc(sizeof(T));
		}
		~handle()
		{
			if (ptr)
				free(ptr);
		}
		void empty()
		{
			return (ptr == nullptr);
		}

		int type()
		{
			if (typeid(T) == typeid(io::blockdev))
				return DEV_HANDLE;
			return -1;
		}
	};
}
