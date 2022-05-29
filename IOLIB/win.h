#pragma once
#include <Windows.h>
#include "color.h"

namespace io
{
	void msgbox(const char* title,const char* text)
	{
		MessageBoxA(nullptr, text, title, MB_OK | MB_ICONASTERISK);
	}

	class window
	{
	private:
		HWND hnd;
	public:
		window(HWND os_handle)
		{
			hnd = os_handle;
		}
		void get_title(char* str)
		{
			if (str == nullptr)
				return;
			GetWindowTextA(hnd, str, strlen(str));
		}
	};

	window get_win()
	{
		return window(GetForegroundWindow());
	}

	class console // adding console gfx
	{
	private:
		HDC dc;
	public:
		console()
		{
			dc = GetWindowDC(GetConsoleWindow());
		}
		void setpixel(int x, int y, io::color clr)
		{
			int rgb[3];
			clr.rgba(rgb);
			COLORREF val = RGB(rgb[0], rgb[1], rgb[2]);
			SetPixel(dc, x, y, val);
		}
	};
}