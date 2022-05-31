#pragma once
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <fstream>

int main(int argc, char** argv)
{
	if (argc < 1)
		return -1;

	if (strcmp(argv[1], "--cr") == 0) // creates an project
	{
		if (argv[2] == nullptr) return -1;
		std::fstream x(argv[2]);
		x << "#include " << '"' << "core.h" << '"' << "\n\n" << "int main() { \nio::prints(" << '"' << "Hello World!" << '"' << ");\n}";

	}

	if (strcmp(argv[1], "--r") == 0) // runs a project
	{
		if (system("g++"))
		{
			char buf[100];
			snprintf(buf, sizeof(buf), "%s %s", "g++ -std=c++11", argv[2]);
			system(buf);
		}
		else if (system("clang"))
		{

		}
	}
#ifdef _WIN32
	system("pause");
#endif
}