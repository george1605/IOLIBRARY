#include "sdl.h"
#include "smath.h"
#include "html.h"
#include <iostream>

int main(int argc, char** argv)
{
	io::uuid x = io::new_uuid();
	io::gen_uuid(x);
	io::printu(x);
	io::free_uuid(x);
	io::pause();
	// uses system("pause")
	return 0;
}