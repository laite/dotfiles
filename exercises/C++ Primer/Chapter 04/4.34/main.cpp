// Ex 4.34: characters, arrays and pointers. and vectors!

#include "../Ch4headers.h"

int main()
{
	vector<string> sVector;
	string s;

	cout << "Please type some words (end with Ctrl+d)." << endl;

	// read some strings into a vector (word per vector element)
	while (cin >> s)
		sVector.push_back(s);

	// We need an array of character pointers (as many pointers as there are typed words)
	const char **characterPointerArray = new const char*[sVector.size()];
	const char **cPA = characterPointerArray; // we'll handle our dynamic array through another pointer

	// Then we'll read vector items one-by-one and create pointers in array
	for (vector<string>::const_iterator vStringIter = sVector.begin(); vStringIter != sVector.end(); ++vStringIter)
	{
		*cPA = (*vStringIter).c_str(); // *cPA = const char*
		++cPA;
	}

	cPA = &characterPointerArray[0]; // return our pointer to zero

	// Then print both vector and array
	cout << endl << "* Printing contents of vector * " << endl;
	for (vector<string>::const_iterator vStringIter = sVector.begin(); vStringIter != sVector.end(); ++vStringIter)
		cout << *vStringIter << endl;

	cout << "* Printing contents of array * " << endl;
	for (const char **cPAEnd = cPA + sVector.size(); cPA != cPAEnd; ++cPA)
		cout << *cPA << endl;

	delete [] characterPointerArray; // finally delete array of new const char*

	return 0;
}
