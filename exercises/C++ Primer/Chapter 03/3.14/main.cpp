// Ex 3.14: strings in a vector

#include "../Ch3headers.h"

int main()
{
	cout << "* Please type some text *" << endl;

	vector<string> sVec;
	string s;

	while (cin >> s)
		sVec.push_back(s);

	for (vector<string>::size_type vi = 0; vi < sVec.size(); ++vi)
	{
		for (string::size_type si = 0; si < sVec[vi].size(); ++si)
			sVec[vi][si] = toupper(sVec[vi][si]);

		// cut line on every eighth word (remember that list starts from zero!)
		if ((vi+1)%8 == 0){
			cout << sVec[vi] << endl;
		}
		else {
			cout << sVec[vi] << " ";
		}
	}

	return 0;
}
