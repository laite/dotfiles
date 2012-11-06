// Ex 5.09: expressions

#include "../Ch5headers.h"

int main()
{
	cout << "Give me four numbers so that first is smaller than second, second smaller than third and so on." << endl;

	int a, b, c, d;
	cin >> a >> b >> c >> d;

	if (a < b && b < c && c < d)
		cout << "Seems to be so." << endl;
	else
		cout << "Nope. " << endl;

	return 0;
}
