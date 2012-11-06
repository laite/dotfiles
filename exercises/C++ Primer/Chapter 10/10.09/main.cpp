// Ex 10.9: word counts with map

#include "../../helpers.h"

int main()
{
	map<string, int> wordCount;
	string s;

	cout << "Please give some words and I'll count their instances, I really do!" << endl;

	while (cin >> s)
		++wordCount[s];

	map<string, int>::iterator wordCountIter = wordCount.begin();

	while (wordCountIter != wordCount.end())
	{
		cout << wordCountIter->first << ": " << wordCountIter->second << endl;
		++wordCountIter;
	}

	return 0;
}
