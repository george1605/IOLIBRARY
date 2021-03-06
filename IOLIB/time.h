#pragma once
#include "core.h"
#include <chrono>
#include <thread>
#if defined(__APPLE__) || defined(__MACH__)
#include <mach/mach_time.h>
#endif
#ifdef _WIN32
#include <synchapi.h>
#endif

namespace io
{

#if defined(__KERNEL__) || defined(_KERNEL_)
	void nop()
	{
		asm("nop");
	}
#endif

	void sleep(size_t x)
	{
#ifdef _WIN32
		Sleep((DWORD)x);
#endif
	}

	void wait(size_t ms = 1000)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds((long long)ms));
	}

	void time()
	{
#ifdef __APPLE__ // even though i don't like it
#include <mach/mach_time.h>
		mach_absolute_time();
#endif
	}
}