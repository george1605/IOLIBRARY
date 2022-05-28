#pragma once
#include <gl/GL.h>
#include <gl/GLU.h>
#include "smath.h"
#include "sdl.h" // use sdl for it's ui

namespace io
{
	bool has_gl()
	{
		return loadlib((char*)LIB(GL_LIB)) != NULL;
	}
	
	void gl_init()
	{
		SDL_Init(SDL_INIT_EVERYTHING);

	}
}