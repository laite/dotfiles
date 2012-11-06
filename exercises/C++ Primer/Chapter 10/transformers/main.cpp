// Word transforming

#include "../../helpers.h"

int main(int argc, char **argv)
{
	map<string, string> wordTransformations;

	if (argc != 3)
		throw runtime_error("USAGE: a.out WORDMAP MESSAGE");

	// first argument should be wordtransforming tables
	ifstream wordTransformingFile(argv[1]);
	if (!wordTransformingFile)
		throw runtime_error("Bad wordmap");

	// build the map of replaceable words
	string oldWord, newWord;
	while (wordTransformingFile >> oldWord >> newWord)
		wordTransformations[oldWord] = newWord;

	// close file
	wordTransformingFile.close();

	ifstream messageStream(argv[2]);
	if (!messageStream)
		throw runtime_error("Bad message file");

	string word;
	while (messageStream >> word)
	{
		// check if word exists in map of replaceable words
		map<string, string>::iterator wordIter = wordTransformations.find(word);
		// print either old or new word
		if (wordIter != wordTransformations.end())
			cout << wordIter->second << " ";
		else
			cout << word << " ";
	}

	messageStream.close();
	cout << endl;

	return 0;
}
