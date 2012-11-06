// Ex 10.05: defining maps

#include "../../helpers.h"

int main()
{
	map< string, list<int> > lineNumbersOfWords;
	map< vector<int>::iterator, int > map1;
	map< list<int>::iterator, int > map2; // this is not valid; no order in list<int>::iterators!
	map< pair<int, string>, int > map3;

	pair<int, string> testPair1(10, "this"), testPair2(10, "that");
	
	if (testPair1 < testPair2)
		cout << "1 smaller" << endl;
	else
		cout << "2 smaller" << endl;


	return 0;
}
