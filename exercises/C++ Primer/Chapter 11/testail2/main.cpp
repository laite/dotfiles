// testailua, pt2

#include "../../helpers.h"

// two 'predicate' functions
bool isShorter(const string &s1, const string &s2)
{
	return s1.size() < s2.size();
}
bool GT6(const string &s)
{
	return s.size() >= 6;
}

int main()
{
	// TEST: finding words that have six or more characters
	const char* sentence[] = { "the", "quick", "red", "fox", "jumps", "over", "the", "slow", "red", "turtle" };
	vector<string> words(sentence, sentence + 10);

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
	vector<string>::size_type wordCount = count_if(words.begin(), words.end(), GT6);

	cout << "There's " << wordCount << " word(s) longer than six characters." << endl;

	// print out the result - words are now ordered 
	// first by size, and for each individual size by alphabet
	PrintVector(words);
	
	// TEST2 : this is cool!
	cout << "Test 2: please enter some integers!" << endl;

	istream_iterator<int> cin_iter(cin);
	istream_iterator<int> eof_iter; // empty iter is interpreted as eof
	vector<int> vec(cin_iter, eof_iter);

	sort(vec.begin(), vec.end());
	ostream_iterator<int> output(cout, " ");

	cout << "Printing ints through unique_copy: ";
	unique_copy(vec.begin(), vec.end(), output);

	return 0;
}
