#include "smath.h"
#include "file.h"
#include "db.h"
#include "sdl.h"
#include "time.h"

void test_expect()
{
	io::sql_header n{ "One", "Two", "Three" };
	io::print_header(n);
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