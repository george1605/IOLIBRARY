#include "smath.h"
#include "file.h"
#include "mobile.h"
#include "sdl.h"

void test_mobile()
{
	io::printc(io::mobile_dev + 'B');
}

int main(int argc, char** argv)
{
	// uses system("pause")
	io::fs::copy("C:\\Users\\George\\Desktop\\main.txt", "C:\\main.txt");
	test_mobile();
	io::pause();
	return 0;
}