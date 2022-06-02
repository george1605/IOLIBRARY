#pragma once
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/glut.h>
#include <GL/glew.h>
#include "smath.h"
#include "sdl.h" // use sdl for it's ui

namespace io
{
	bool has_gl()
	{
		return loadlib((char*)LIB(GL_LIB)) != nullptr;
	}

	struct gl_rect
	{
		uint32_t x, y;
		uint32_t w, h;
		void draw_to()
		{

		}
	};

	struct gl_coords
	{
		uint32_t x1, y1;
		uint32_t x2, y2;
	};

	class glwin : public sdlwin
	{
	private:
		int handle;
	public:
		glwin() : sdlwin()
		{
			handle = glutGetWindow();
		}
		
		void draw_line(gl_coords x)
		{
			glBegin(GL_LINES);
				glVertex2f(x.x1, x.x2);
				glVertex2f(x.y1, x.y2);
			glEnd();
		}
	};

}