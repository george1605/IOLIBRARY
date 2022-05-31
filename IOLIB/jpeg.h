#pragma once
#include <fstream>
#include "buffer.h"
#if !defined(_str) && !defined(_byte) // i use simmilar macros in other projects
#define _byte unsigned char
#define _str const char*
#define _usename(x) using namespace x
#endif

namespace io
{
#define JPEG_SIZE 1
	struct jfi_header
	{
		_byte SOI[2];          /*  *00h*  Start of Image Marker     */
		_byte APP0[2];         /* 02h  Application Use Marker    */
		_byte Length[2];       /* 04h  Length of APP0 Field      */
		_byte Identifier[5];   /* 06h  "JFIF" (zero terminated) Id String */
		_byte Version[2];      /* 07h  JFIF Format Revision      */
		_byte Units;           /* 09h  Units used for Resolution */
		_byte Xdensity[2];     /* 0Ah  Horizontal Resolution     */
		_byte Ydensity[2];     /* 0Ch  Vertical Resolution       */
		_byte XThumbnail;      /* 0Eh  Horizontal Pixel Count    */
		_byte YThumbnail;      /* 0Fh  Vertical Pixel Count      */
	};

	struct img_buffer
	{
		_byte* Info;
		size_t Length;
		bool is_ok() // checks for the length
		{
			(strlen((_str)Info) == Length);
		}
	};

	void jpeg_read(std::string path, jfi_header* p)
	{
		if (p == nullptr) return;
		std::fstream n(path);
		n.read((char*)p, sizeof(p));
		n.close();
	}

	int jpeg_vers(jfi_header* x)
	{
		if (x == nullptr)
			return 0;

		return x->Version[0] * 100 + x->Version[1];
	}

	void jpeg_print(jfi_header* x, int flags)
	{
		if (flags == JPEG_SIZE)
			printf("%ux%u", x->XThumbnail, x->YThumbnail);
	}

	void jpeg_read(std::string path, img_buffer x)
	{
		if (x.Info == nullptr) return;
		std::fstream n(path);
		n.seekg(sizeof(jfi_header) + 1); // skips the header
		n.read((char*)x.Info, x.Length);
	}

}
