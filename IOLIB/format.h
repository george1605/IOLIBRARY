#pragma once
#include <cmath>
#include <ostream>

namespace format
{
	wchar_t form_char(char base, char dia)
	{
		if (base == 'A' && dia == '`')
			return L'À';
		if (base == 'A' && dia == '/')
			return L'Á';

		return (wchar_t)0xFF;
	}

	class currency
	{
	public:
		double amount;
		wchar_t code = L'$';
		int prec = 4;
		currency(double x, int dec)
		{ 
			prec = dec;
			const double multiplier = std::pow(10.0, dec);
			amount = std::ceil(x * multiplier) / multiplier;
		}
	};

	std::ostream& operator <<(std::ostream& x, currency n)
	{
		x.precision(n.prec);
		x << n.amount;
		return x;
	}
}