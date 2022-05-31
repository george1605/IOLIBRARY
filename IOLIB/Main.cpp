#include "smath.h"
#include "file.h"
#include "mobile.h"
#include "sdl.h"
#include "time.h"

void test_expect()
{
	io::string p = "1000";
	p.reverse();
	std::cout << p;
}

int main(int argc, char** argv)
{
	// uses system("pause")
	void* x = io::mapfile(1);
	test_expect();
	io::unmapfile(x, PAGE_SIZE);
	io::pause();
	return 0;
}