#pragma once
#include "core.h"
#include "file.h"
#include "wsocket.h"
#include "smath.h"
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

	class hash_str
	{
	private:
		io::string _dont;
		int mask;
	public:
		hash_str() {}
		hash_str(io::string x)
		{
			_dont = x;
		}
		void hash()
		{
			mask = io::get_rand(time(nullptr)) & 0x2F;
			io::do_xor((unsigned char*)_dont.addr(), mask); // 
		}
	};

	class db_cred
	{
		io::string host;
		io::string user;
		io::hash_str pwd;
	};

	typedef std::vector<js_value> js_heap;

	class db_file
	{
	private:
		io::file fil;
	public:
		db_file(io::string name)
		{
			fil.open(name);
		}
		void query(io::string q) // does an SQL query
		{

		}
	};
}