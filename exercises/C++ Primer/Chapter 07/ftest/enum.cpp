// Playing some ee-nums

#include "../Ch7Headers.h"

enum simply_red { CLASSIC, CALSIC = 'r'};

namespace mynum {
	enum { ENSIN, JA, SITTEN, TOISEKSI };
}

// scoped enums need -std=c++0x flag
enum class InProgress { None, Command, Key };

// silly overloading
void ff(int a) { cout << "int: " << a << endl; }
void ff(char a) { cout << "char: " << a << endl; }
void ff(unsigned char a) { cout << "uchar: " << a << endl; }

int iiFunction(int a, int b) { return (a+b); }
double iiFunction(double a, double b) { return (a+b); }


int main()
{

	// by default, our 'r' in enum calls ff(int)
	ff(CALSIC);
	// we can make it cast others explicitly, though
	ff(static_cast<unsigned char>(CALSIC));

	cout << iiFunction(15, 16) << endl;
	cout << iiFunction(15.9, 16.99) << endl;
	
	// this is an ambiguous call and won't compile
	// iiFunction(15, 16.99); 


	// ENSIN is in namespace mynum (and defaults to 0)
	cout << mynum::ENSIN << endl;

	InProgress in_progress = InProgress::None;
	cout << ((in_progress == InProgress::Command)? "all is same" : "there is a difference") << endl;

	return 0;
}
