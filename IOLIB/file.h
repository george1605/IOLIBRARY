#pragma once
#include "buffer.h"
#include <filesystem>

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
		void readbuf(io::buffer& buf)
		{
			fread(buf.c_str(), 1, buf.size(), fd[0]);
		}
	} stdio(0, 1);

	class fs {
	public:
		static char* resolve(char* path)
		{
	#include <windows.h>
	#include <Shlwapi.h>
			GetModuleFileName(NULL, path, sizeof(path));

		}

		static void creat(char* nme, int ent)
		{
			if (ent == FILE_ENT)
				CreateFile();
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