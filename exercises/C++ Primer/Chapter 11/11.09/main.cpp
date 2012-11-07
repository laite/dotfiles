// Ex 11.09: counting the words

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
	vector<string> words;
	ifstream file("source"); // it is NOT a good idea to use main.cpp as such

	string s;
	while (file >> s)
	{
		size_t found;
		// remove some non-alphabetics
		while ((found = s.find_first_of(",;()[]")) != string::npos)
			s.erase(found,1);
		words.push_back(s);
	}

	file.close();

	/* FIRST: eliminating duplicates from vector of strings */

	// sort words for unique()
	sort(words.begin(), words.end());
	// unique leaves unique words in front and returns iterator where 'rest of the words' begin
	vector<string>::iterator endOfUnique = unique(words.begin(), words.end());
	// erase from first non-unique to end through container operator
	words.erase(endOfUnique, words.end());

	/* SECOND: counting the words */
	
	// stable sort leaves 'equal' words in place (equal here means 'as long as'), so we maintain 
	// alphabetic order per each wordlength!
	stable_sort(words.begin(), words.end(), isShorter);

	// count_if returns words that fulfill condition GT6
	vector<string>::size_type wordCount = count_if(words.begin(), words.end(), GT);

	cout << "There's " << wordCount << " word(s) longer than " << kCharLength << " characters." << endl;

	// print out the result - words are now ordered 
	// first by size, and for each individual size by alphabet
	PrintVector(words);
	
	return 0;
}
