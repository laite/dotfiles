// String testing 2: The fun thickens

#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::endl;

int main()
{
	string s1("Ex4mpl3 ? string");

	for (string::size_type si = 0; si != s1.size(); ++si)
		cout << (isalpha(s1[si])? "A" : "B") << endl;

	return 0;
}
