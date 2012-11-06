// Ex 9.39: words in sentences
// take 2

#include "../../helpers.h"

void ResetWord(short &oldWord, short &oldWordCount, short newWord, short newCount)
{
	oldWord = newWord;
	oldWordCount = newCount;
}

int main()
{
	string line1 = "We are her pride of 10 she named us";
	string line2 = "Benjamin, Phoenix, the Prodigal";
	string line3 = "and perspicacious pacific Suzanne";

	string sentence = line1 + ' ' + line2 + ' ' + line3;
	short wordCount = 0, shortestWord, longestWord;
	short longestWordCount = 0, shortestWordCount = 0;

	istringstream sStream(sentence);
	string word;

	while (sStream >> word)
	{
		if (wordCount++ == 0)
		{
			shortestWord = longestWord = word.size();
			shortestWordCount = longestWordCount = 1;
		}
		else if (word.size() < shortestWord)
			ResetWord(shortestWord, shortestWordCount, word.size(), 1);
		else if (word.size() == shortestWord)
			shortestWordCount++;
		else if (word.size() > longestWord)
			ResetWord(longestWord, longestWordCount, word.size(), 1);
		else if (word.size() == longestWord)
			longestWordCount++;
	}

	cout << "Total words: " << wordCount << endl;
	cout << "Shortest: " << shortestWord << " (" << shortestWordCount << ")" << endl;
	cout << "Longest: " << longestWord << " (" << longestWordCount << ")" << endl;

	return 0;
}
