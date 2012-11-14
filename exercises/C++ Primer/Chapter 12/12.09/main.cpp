// Ex 12.09: Screen+Cursor, toying with

#include "../../helpers.h"
#include "../Screen.h"

int main()
{
	Screen testScreen(100, 10);
	Cursor cursor(65, 2);

	testScreen.RandomizeContent();
	cout << "get(65,2)  : " << testScreen.get(65, 2) << endl;
	cout << "get(cursor): " << testScreen.get(cursor) << endl;

	return 0;
}
