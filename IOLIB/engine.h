#pragma once
#include "gl.h"

namespace io
{

	class game_object
	{
	public:
		game_object() {}
		io::vector2 velocity;
	};

	class player : public game_object
	{
	public:
		size_t hp = 100;
		player()
		{

		}
	};

	class background
	{
	public:
		void draw()
		{
			
		}
	};
}