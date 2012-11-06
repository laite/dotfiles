// Ex 4.14: pointers and values

#include "../Ch4headers.h"

int main()
{
	int ival = 1024, ival2 = 2048;
	int *p = &ival;

	cout << "int *p = &ival" << endl;
	cout << "pointer: " << *p << " ival: " << ival << " ival2: " << ival2 << endl;
	cout << "p = &ival2" << endl;
	p = &ival2;
	cout << "pointer: " << *p << " ival: " << ival << " ival2: " << ival2 << endl;
	cout << "*p = ival" << endl;
	*p = ival;
	cout << "pointer: " << *p << " ival: " << ival << " ival2: " << ival2 << endl;
	cout << "ival2 = 64" << endl;
	ival2 = 64;
	cout << "pointer: " << *p << " ival: " << ival << " ival2: " << ival2 << endl;

	// references
	
	int &r = ival;

	cout << "int &r = ival" << endl;
	cout << "r: " << r << " ival: " << ival << " ival2: " << ival2 << endl;
	cout << "r = ival2" << endl;
	r = ival2;
	cout << "r: " << r << " ival: " << ival << " ival2: " << ival2 << endl;
	cout << "ival2 = 1000" << endl;
	ival2 = 1000;
	cout << "r: " << r << " ival: " << ival << " ival2: " << ival2 << endl;
	
	return 0;
}
