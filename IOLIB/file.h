#pragma once
#include "buffer.h"
#ifdef _WIN32
#include <windows.h>
#include <Shlwapi.h>
#include <direct.h>
#else
#include <fcntl.h>
#include <unistd.h>
#endif

namespace io
{
#define FILE_ENT 1
#define DIR_ENT 2
#define DEV_ENT 4

	__DENIED FILE* from_fd(int x)
	{
		if (x < 0)
			return (FILE*)NULL;
		if (x == 0)
			return stdin;
		else if (x == 1)
			return stdout;
		else
			return (FILE*)x;
	}

	class file
	{
	private:
		FILE* fd[2];
	public:
		file(int fd0, int fd1 = 1)
		{
			fd[0] = from_fd(fd0);
			fd[1] = from_fd(fd1);
			if (fd[0] == NULL || fd[1] == NULL)
				io::error = ENOFILE;
		}
		file(const char* fname)
		{
			fd[0] = fopen(fname, "r");
			fd[1] = fopen(fname, "w");
		}
		void readbuf(io::buffer& buf)
		{
			fread(buf.c_str(), 1, buf.size(), fd[0]);
		}
		void writebuf(io::buffer& buf)
		{
			fwrite(buf.c_str(), 1, buf.size(), fd[1]);
		}
		file operator <<(std::string x)
		{
			fwrite(x.c_str(), 1, x.size(), fd[1]);
			return *this;
		}
	} stdio(0, 1);

	class fs {
	public:
		static char* resolve(char* path)
		{
#ifdef _WIN32
			GetModuleFileNameA(NULL, path, sizeof(path));
#endif
		}

		static void creat(char* nme, int ent)
		{
#ifdef _WIN32
			if (ent == FILE_ENT)
				CreateFileA(nme, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
			else
				_mkdir(nme);
#endif
		}

		static void creat(const char* nme, int ent)
		{
			creat((char*)nme, ent);
		}
	};

	class vfs { // creates a virtual filesystem
	private:
		io::llink root;
	public:
		vfs()
		{
			
		}
		void addFile(char* fname)
		{
			root.add();
			root.next->value = (long)fname;
		}
	};
}