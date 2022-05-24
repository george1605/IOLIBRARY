#pragma once
#include "core.h"
#ifdef __linux__
#include <X11/Xlib.h>

namespace io
{
	typedef XEvent xevt;
	void x11_setup() {}

	class window
	{
	protected:
		Window win;
	public:
		window()
		{

		}

		void create()
		{

		}
	};

	class display
	{
	protected:
		Display* info;
	public:
		display()
		{
			info = XOpenDisplay(NULL);
		}

		~display()
		{
			XCloseDisplay(info);
		}

		Display* handle()
		{
			return info;
		}
	};

	void get_xevt(display p, xevt& n)
	{
		XNextEvt(p.handle(), &n);
	}
}
#else
namespace io
{
	void x11_setup()
	{
		io::error = ENOX11;
	}
}
#endif