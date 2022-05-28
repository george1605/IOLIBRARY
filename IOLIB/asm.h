#pragma once
#include "core.h"
#include "file.h"
#include <string>
#define INTEL_ASM 0
#define ATT_ASM 1 // AT&T / GNU
#define ARM_ASM 2
#define AVR_ASM 3

namespace io
{
	int asm_type = INTEL_ASM;
	void set_asm()
	{
#ifdef __ARM__
		asm_type = ARM_ASM;
#elif defined(_WIN32) 
		asm_type = INTEL_ASM;
#elif defined(__GNUC__) || defined(_UNIX_)
		asm_type = ATT_ASM;
#elif defined(__AVR__)
		asm_type = AVR_ASM;
#endif
	}
	std::string asm_plus(int x, int y)
	{
		std::string n = "mov eax, " + std::to_string(x) + "\n";
		n = n + "mov ebx, " + std::to_string(y) + "\n";
		n = n + "add eax, ebx"; // haha, building an assembler from ground up
		return n;
	}

	std::string asm_stack()
	{
		return std::string("mov ebx, [ebp]");
	}

	void new_asm(std::string fname)
	{
		io::fs::creat((char*)fname.c_str(), FILE_ENT);
	}
}