#include "smath.h"
#include "file.h"
#include "mobile.h"
#include "sdl.h"
#include "time.h"

void test_expect()
{
	io::buffer x(4);
	io::expect<char> n(0);
	n = x[5];
	n.error().print();
}

int main(int argc, char** argv)
{
	// uses system("pause")
	io::fs::copy("C:\\Users\\George\\Desktop\\main.txt", "C:\\main.txt");
	test_expect();
	io::pause();
	return 0;
}