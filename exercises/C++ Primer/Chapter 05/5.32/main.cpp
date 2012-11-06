// Ex 5.32: implicit type conversions

#include "../Ch5headers.h"

int main()
{
	char cval = 3;
	int ival = 3;
	unsigned int ui = 3;
	float fval = 3.0;
	double dval = 4.0;

	/* all comments are my GUESSES, not necessarily true as such! */

	// 'a' is char, and so is 3 - no type conversions here
	cval = 'a' + 3;

	// ival converted to float, so is ui(?)
	fval = ui - ival * 1.0;

	// ui is converted to float, then result of multiplification to double
	dval = ui * fval;

	// all right-side values converted to double, then char (%256) as assignment ('=')
	cval = ival + fval + dval;

	cout << (int)cval << endl;

	return 0;
}
