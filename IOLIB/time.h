#pragma once
#include "core.h"
#include <thread>
#include <chrono>
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

	void wait(size_t ms = 1000)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(ms));
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