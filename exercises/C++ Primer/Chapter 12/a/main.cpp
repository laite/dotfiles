// Ex 12.

#include "../../helpers.h"

int main()
{
	// c++0x style initializing
	vector<string> sVec { "a", "b" };

	// this prints out "b"
	cout << sVec.at(1) << endl;

	return 0;
}
