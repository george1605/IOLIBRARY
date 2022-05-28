#pragma once
#include <cmath>
#include <ostream>

namespace io
{
#define G_CONST 6.6743e-11
	const double PI = 2.0 * acos(0.0);
	double delta(double a, double b, double c)
	{
		return sqrt(b * b - 4 * a * c);
	}

	int pows2(int n) // the biggest power of 2 smaller than n
	{
		int k = 1;
		while (k < n)
			k *= 2;

		return (k / 2);
	}

	long double gravity(double mass1, double mass2, double r)
	{
		return ((long double)G_CONST * mass1 * mass2) / (r * r);
	}

	long get_bytes(double& x) // quake style ptr switching
	{
		return *(long*)&x;
	}

	int fact(int n) // recursive factorial
	{
		if (n == 1)
			return 1;
		return n * fact(n - 1);
	}

	class vector2
	{
	public:
		double x, y;
		vector2() : x(1), y(1) {}
		vector2(double x, double y)
		{
			this->x = x;
			this->y = y;
		}
		vector2 operator *(vector2& n)
		{

			return *this;
		}
		vector2 operator *(int k)
		{
			this->x *= k;
			this->y *= k;
			return *this;
		}

		double mod()
		{
			return sqrt(x * x + y * y);
		}
	};

	std::ostream& operator << (std::ostream& x, vector2 n)
	{
		x << "(" << n.x << ", " << n.y << ")";
		return x;
	}

	void do_xor (int v[], int mask) // encryption !!!
	{
		for (int a = 0; v[a] != 0; a++)
			v[a] = v[a] ^ mask;
	}

	void do_xor (unsigned char bytes[], int mask)
	{
		for (int a = 0; bytes[a] != 0; a++)
			bytes[a] = (char)(bytes[a] ^ mask);
	}
}