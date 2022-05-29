#pragma once
#include <stdlib.h>
#include <windows.h>
#include "core.h"

namespace io
{
	typedef void* dlib;
	typedef void* slib;
	typedef void(*main_func)(int argc, char** argv);

	void std_exec(main_func x)
	{
		if (x == nullptr) return;
		x(0, (char**)0);
	}
#ifdef _WIN32
#define USB_LIB "UsbTask.dll"
#define SDL_LIB "SDL2.dll"
#define GL_LIB "GLU.dll"
#define LIB(x) "C:\\Windows\\System32\\" ## x
	dlib loadlib(char* name)
	{
		if (name == nullptr)
			return nullptr;
		return (dlib)LoadLibraryA(name);
	}

	void* getfunc(dlib x, char* name)
	{
		return (void*)GetProcAddress((HMODULE)x, name);
	}
#endif

#ifdef __linux__
#include <fcntl.h>
#define LIB(x) "/usr/local/lib" ## x

	dlib loadlib(char* name)
	{
		return (dlib)open(name, O_EXEC);
	}
#endif

#ifdef __APPLE__

#endif
}