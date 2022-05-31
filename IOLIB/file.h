#pragma once
#include "buffer.h"
#include <fstream>
#ifdef _WIN32
#include <windows.h>
#include <Shlwapi.h>
#include <direct.h>
#else
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#endif

namespace io
{
#define FILE_ENT 1
#define DIR_ENT 2
#define DEV_ENT 4

	std::fstream from_fd(int x)
	{
		if (x < 0)
			return std::fstream();
		if (x == 0)
			return std::fstream(stdin);
		else if (x == 1)
			return std::fstream(stdout);
		else
			return std::fstream((FILE*)x);
	}

	void* mapfile(int fd, size_t size = PAGE_SIZE, void* ptr = nullptr)
	{
#ifdef _UNIX_
		return mmap(ptr, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
#else
		return malloc(size);
#endif
	}

	void unmapfile(void* ptr, size_t size)
	{
#ifdef _UNIX_
		munmap(ptr, size);
#else
		if (ptr)
			free(ptr);
#endif
	}

	class file
	{
	private:
		std::fstream fd[2];
	public:
		file() {}
		file(int fd0, int fd1 = 1)
		{
			fd[0] = from_fd(fd0);
			fd[1] = from_fd(fd1);
			if (fd[0].fail() || fd[1].fail())
				io::error = ENOFILE;
		}
		file(const file& f)
		{

		}
		file(const char* fname)
		{
			fd[0] = std::fstream(fname, std::fstream::in);
			fd[1] = std::fstream(fname, std::fstream::out);
		}
		void readbuf(io::buffer& buf)
		{
			fd[0].read(buf.c_str(), buf.size());
		}
		void writebuf(io::buffer& buf)
		{
			fd[1].write(buf.c_str(), buf.size());
		}
		file operator <<(std::string x)
		{
			fd[1].write(x.c_str(), x.size());
			return *this;
		}
		void open(io::string fname)
		{
			fd[0] = std::fstream(fname.addr(), std::fstream::in);
			fd[1] = std::fstream(fname.addr(), std::fstream::out);
		}
	} stdio(0, 1);

	class fs {
	public:
		static char* resolve(char* path)
		{
#ifdef _WIN32
			GetModuleFileNameA(nullptr, path, sizeof(path));
#endif
		}

		static void creat(char* nme, int ent)
		{
#ifdef _WIN32
			if (ent == FILE_ENT)
				CreateFileA(nme, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, nullptr);
			else
				_mkdir(nme);
#else
			if (ent == FILE_ENT)
				creat(nme, O_RDONLY | O_WRONLY);
			else
				mkdir(nme);
#endif
		}

		static void creat(const char* nme, int ent)
		{
			creat((char*)nme, ent);
		}

		static bool copy(const char* file1, const char* file2)
		{
#ifdef _WIN32
			return (bool)CopyFileA(file1, file2, FALSE);
#endif
			return true;
		}

		static std::string to_posix(std::string x)
		{
		}
	};

	class vfs { // creates a virtual filesystem
	private:
		io::llink root;
	public:
		vfs()
		{

		}
		vfs(const char* root_name)
		{
			root.value = (long)root_name;
		}
		void addFile(char* fname)
		{
			root.add();
			root.next->value = (long)fname;
		}
	};

	struct term_cell
	{
		int X, Y;
		char cnt; // current char
	};

	class terminal
	{
	private:
#ifdef _WIN32
		HANDLE console;
#endif
#ifdef __linux__
		struct termios console;
#endif
	public:
		int number = 0; // like TTYS0 
		terminal()
		{
#ifdef _WIN32
			console = GetStdHandle(STD_OUTPUT_HANDLE);
#elif defined(__linux__)
			tcgetattr(0, &console);
#endif
		}
		terminal(int x)
		{
			number = x;
		}

		bool write(io::term_cell c)
		{
#ifdef _WIN32
			COORD n = { c.X, c.Y };
			DWORD err;
			WriteConsoleOutputCharacterA(console, &c.cnt, 1, n, &err);
			if (err == 0)
				return false;
			return true;
#endif
		}
	};
}
