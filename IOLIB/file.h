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

        void* mapfile(int fd, size_t size = 4096, void* ptr = nullptr)
        {
        #ifdef _UNIX_
          return mmap(ptr, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
        #else
          return malloc(size);
        #endif
        }

	class file
	{
	private:
		std::fstream fd[2];
	public:
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
}
