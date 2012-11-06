// Ex 10.23: exclude words with vector instead of set

#include "../../helpers.h"
#include <algorithm>

int main()
{
	vector<string> excludedWordsVector;
	ifstream excludedWordStream("excluded");

	if (!excludedWordStream)
		throw runtime_error("Can't find words to exclude!");

	string badWord;
	while (excludedWordStream >> badWord)
		excludedWordsVector.push_back(badWord);

	excludedWordStream.close();

	// with set, we would be done by now
	// with vector we still have to check for duplicates!
	sort( excludedWordsVector.begin(), excludedWordsVector.end() );
	excludedWordsVector.erase( unique( excludedWordsVector.begin(), excludedWordsVector.end() ), excludedWordsVector.end() );

	return 0;
}
