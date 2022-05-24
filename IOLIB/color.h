#pragma once
#include "core.h"

namespace io
{
	class color
	{
	private:
		int value;
		int r, g, b;
	public:
		color(int x)
		{
			value = x;
		}

		color(int r, int g, int b)
		{
			this->r = r, this->g = g, this->b = b;
		}

		void invert()
		{
			r = 255 - r;
			g = 255 - g;
			b = 255 - b;
		}

		void rgba(int arr[3])
		{
			arr[0] = r;
			arr[1] = g;
			arr[2] = b;
		}
	};
}