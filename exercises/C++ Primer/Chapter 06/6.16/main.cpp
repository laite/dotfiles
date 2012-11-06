// Ex 6.16: prefix of a vector

#include "../Ch6headers.h"

int main()
{
	vector<int> iVec1;

	for (int i = 0; i != 10; ++i)
		iVec1.push_back(i);

	vector<int> iVec2(iVec1);
	iVec2.push_back(13);
	iVec2.push_back(14);

	// take shorter vector as size 
	vector<int>::size_type iVecShorter = (iVec1.size() > iVec2.size())? iVec2.size() : iVec1.size();

	bool areSame = true;
	for (vector<int>::size_type iVecSize = 0; iVecSize != iVecShorter; ++iVecSize)
	{
		if (iVec1[iVecSize] != iVec2[iVecSize])
		{
			areSame = false;
			break;
		}
	}

	if (areSame)
		cout << "Yep, same as far..." << endl;
	else
		cout << "Differ." << endl;

	return 0;
}
