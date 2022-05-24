#pragma once
#include "core.h"
#if defined(__APPLE__) || defined(__MACH__)
#include <mach/mach_time.h>
#endif

namespace io
{
	void sleep(int x)
	{
#ifdef _WIN32
		#include <Windows.h>
		Sleep((DWORD)x);
		
#endif
	}

	void time()
	{
#ifdef __APPLE__ // even though i don't like it
#include <mach/mach_time.h>
		mach_absolute_time();
#endif
	}
}

#if defined(__KERNEL__) || defined(_KERNEL_)
void nop()
{
	asm("nop");
}
#endif