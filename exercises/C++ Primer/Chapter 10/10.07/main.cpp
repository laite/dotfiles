// Ex 10.7: Types defined by map

#include "../../helpers.h"

int main()
{
	map<int, vector<int> > vecIndexMap;
	map<int, vector<int> >::key_type vecIndexMapType = 12; // key_type is int
	map<int, vector<int> >::mapped_type vecIndexKeyType(4,10); // mapped_type is vector<int>

	vecIndexMap.insert(pair<int, vector<int> >(vecIndexMapType, vecIndexKeyType));
	map<int, vector<int> >::iterator mapIter = vecIndexMap.begin();

	if (mapIter == vecIndexMap.end())
		cout << "It really is." << endl; // there ain't any items in vecIndexMap
	else
		cout << "Size is: " << vecIndexMap.size() << endl;

	if (!vecIndexMap.empty())
	{
		mapIter = vecIndexMap.begin();
		cout << "Key: " << mapIter->first << "\nValue: ";
		PrintVector(mapIter->second);
	}

	return 0;
}
