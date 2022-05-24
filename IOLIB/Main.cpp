#include "sdl.h"
#include "smath.h"
#include "html.h"
#include <iostream>
#include "x11.h"

int main(int argc, char** argv)
{
	// uses system("pause")
	io::x11_setup();
	io::print_err();
	io::pause();
	return 0;
}