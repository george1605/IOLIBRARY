#pragma once
#include <stdlib.h>

#ifdef __ARM__

namespace io
{
#define PPBI_BASE 0
#define ITM_BASE 0
#define DWT_BASE 1

	void* arm_mmap[] = {
		(void*)0xE0000000U,
		(void*)0xE0001000U
	};

	void mmiow(void* addr, int value)
	{
		if (addr == NULL) return;
		*(volatile int*)addr = value;
	}

	int mmior(void* addr)
	{
		if (addr == NULL) return;
		return (*(volatile int*)addr);
	}

	void nop()
	{
		asm("mov r0, r0");
	}
}

#endif
