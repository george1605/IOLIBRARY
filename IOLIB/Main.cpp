#include "smath.h"
#include "file.h"
#include "mobile.h"
#include "sdl.h"
#include "time.h"

void test_expect()
{
	
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