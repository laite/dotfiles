// Ex 7.35 / function declarations, overloading and some

#include "../Ch7Headers.h"

int calc(const int a, const int b)
{
	return a+b;
}

// int calc(int a, int b) { } // not allowed overriding: function calls are 'ambiguous' with calc(const int, const int)

// reset without & would only change local copy of pointer
void reset(int *&i) { *i = 0; i = 0; return; }
void reset(double *&d) { *d = 0.0; d = 0; return; }

int main()
{
	int a = 1, b = 2;
	const int c = 3, d = 4;
	double dd = 66.66;

	cout << calc(a, b) << endl << calc(c, d) << endl;

	int nn = calc(a,calc(b,c));
	int mm = 11 + calc(d,c);

	cout << nn << endl << mm << endl;

	double *pd = &dd;

	int *pi = &b;
	cout << "address of *pi: " << pi << endl;
	reset(pi);
	cout << "address of *pi: " << pi << endl;

	return 0;
}
