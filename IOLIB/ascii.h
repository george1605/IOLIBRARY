#pragma once
// ascii font like 
// ***
// * *
// ***
#include "ttf.h"
#include "sdl.h"
#include "file.h"

namespace io
{
	void draw_ascii(io::sdlrender rend, io::string ascii, int xstart = 100, int ystart = 100)
	{
		int cx = xstart, cy = ystart;
		for (int a = 0; ascii[a] != '\0'; a++)
		{
			if (ascii[a] == '*' || ascii[a] == '#')
				SDL_RenderDrawPoint(rend, cx, cy), cx++;
			if (ascii[a] == '\n')
				cx = xstart, cy++;
		}
	}
}