#pragma once
#include <cstdlib>
#include <cstring>

namespace io
{
	typedef float* ai_weights;
	typedef float* ai_input;

	void ml_init(ai_weights w, size_t size)
	{
		if (w == NULL)
			w = (float*)malloc(size * sizeof(float));
		std::memset(w, 0, size);
	}
}