#pragma once
#include "core.h"
#include <map>

namespace io
{
	class htmlelem
	{
	public:
		char tag[8];
		std::map<char*, void*> props;
		htmlelem()
		{

		}
		~htmlelem()
		{

		}
	};

	htmlelem parse(char* string)
	{
		htmlelem x;
		int c = 1;
		while (string[c] != ' ' && string[c] != '\0')
		{
			x.tag[c - 1] = string[c];
		}
		x.tag[7] = '\0';
		return x;
	}
}