#pragma once
#include "core.h"

namespace io
{
	class color
	{
	private:
		uint32_t value;
		uint8_t r, g, b;
	public:
		color(int x)
		{
			value = x;
		}

		color(uint8_t r, uint8_t g, uint8_t b)
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

		void rand() // random color ?
		{
			int k = time(NULL);
			r = get_rand(k) % 256;
			g = get_rand(k) % 256;
			b = get_rand(k) % 256;
		}
	};
}