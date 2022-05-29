#pragma once
#include "core.h"
#include "file.h"
#include "wsocket.h"
#include <string>

namespace io
{
	// JSON Parsing - for MongoDB -
	typedef enum {
		STRING,
		NUMBER,
		BOOL,
		ARRAY,
		OBJECT
	} js_types;

	class js_value
	{
	private:
		char* mem;
		size_t size;
	public:
		js_types type;
		js_value(int n)
		{
			type = js_types::NUMBER;
		}
		js_value(std::string p)
		{
			type = js_types::STRING;
		}
		~js_value()
		{
			memset((void*)mem, 0, size);
		}
	};

	js_types obj_type(std::string js_str)
	{
		if (js_str[0] == '[')
			return js_types::ARRAY;
		if (js_str[0] == '{')
			return js_types::OBJECT;
		if (js_str.find("true") != std::string::npos || js_str.find("false") != std::string::npos)
			return js_types::BOOL;
		return js_types::OBJECT;
	}

	std::vector<js_value> json_parse(std::string object)
	{
		return std::vector<js_value> { js_value(0) };
	}

	class db_cred
	{

	};

	typedef std::vector<js_value> js_heap;
}