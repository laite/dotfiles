// Ex 3.16: 3x42

#include "../Ch3headers.h"

int main()
{
	cout << "* Example begins *" << endl;

	vector<int> a(10);
	vector<int> b(10,42);
	vector<int> c;

	for (int i = 0; i < 10; ++i){
		a[i] = 42;
		c.push_back(42);
	}

	cout << "a) ";
	for (vector<int>::size_type vi=0; vi < a.size(); ++vi)
		cout << a[vi];

	cout << endl << "b) ";
	for (vector<int>::size_type vi=0; vi < b.size(); ++vi)
		cout << b[vi];

	cout << endl << "c) ";
	for (vector<int>::size_type vi=0; vi < c.size(); ++vi)
		cout << c[vi];

	cout << endl;

	return 0;
}
