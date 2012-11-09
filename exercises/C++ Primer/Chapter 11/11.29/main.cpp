// Ex 11.29: counting the words (modified from ex. 11:09)

#include "../../helpers.h"

// define how long words we're looking for
const int kCharLength = 8;

// two 'predicate' functions
bool isShorter(const string &s1, const string &s2)
{
	return s1.size() < s2.size();
}
bool GT(const string &s)
{
	return s.size() >= kCharLength;
}

int main()
{
	list<string> words;
	ifstream file("source"); // it is NOT a good idea to use main.cpp for this :)

	string s;
	while (file >> s)
	{
		size_t found;
		// remove some non-alphabetics
		while ((found = s.find_first_of(".,\"_'-+=<>!*/\\&:;()[]{}")) != string::npos)
			s.erase(found,1);
		transform(s.begin(), s.end(), s.begin(), ::tolower);
		words.push_back(s);
	}

	file.close();

	/* FIRST: eliminating duplicates from list of strings */

	// sort words for unique()
	words.sort();
	words.unique();
	words.sort(isShorter);

	/* SECOND: counting the words */

	// count_if returns words that fulfill condition GT6
	list<string>::size_type wordCount = count_if(words.begin(), words.end(), GT);

	cout << "There's " << wordCount << " word(s) longer than " << kCharLength << " characters." << endl;

	// print out the result - words are now ordered 
	// first by size, and for each individual size by alphabet
	PrintList(words);
	
	return 0;
}
