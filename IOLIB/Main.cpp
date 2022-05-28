#include "smath.h"
#include "sdl.h"
#include "html.h"
#include "file.h"

int main(int argc, char** argv)
{
	// uses system("pause")
	io::stdio << "123";
	io::fs::creat("C:\\main", DIR_ENT);
	io::exec_cmd("firefox");
	io::pause();
	return 0;
}