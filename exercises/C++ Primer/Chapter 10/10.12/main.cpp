// Ex 10.12: rewriting ex. 10.9 with insert() call

#include "../../helpers.h"

int main()
{
	map<string, int> wordCount;
	string word;

	cout << "Please give some words and I'll count their instances, I really do!" << endl;

	while (cin >> word)
	{
		// insert(value_type) returns pair with iterator to item (wordCount[word]) and 
		// boolean, which is true if insert() added an item, false if key already existed
		pair<map<string, int>::iterator, bool> result = wordCount.insert(make_pair(word, 1));
		if (!result.second)
			++result.first->second; // same as: ++wordCount[word];
	}

	map<string, int>::iterator wordCountIter = wordCount.begin();

	while (wordCountIter != wordCount.end())
	{
		cout << wordCountIter->first << ": " << wordCountIter->second << endl;
		++wordCountIter;
	}

	return 0;
}
