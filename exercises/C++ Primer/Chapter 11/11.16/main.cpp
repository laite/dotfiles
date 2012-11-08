// Ex 11.16: contents of a file

#include "../../helpers.h"

int main(int argc, const char **argv)
{
	string sourceFile("sourcefile");

	if (argc > 1)
		sourceFile = argv[1];

	ifstream file(sourceFile.c_str());

	if (!file)
	{
		cerr << "No file " << sourceFile << " found! Quitting gracefully." << endl;
		return -1;
	}

	// create two iters for begin and end of ifstream
	istream_iterator<string> fileIter(file);
	istream_iterator<string> endIter;

	// output iterator binded to cout
	ostream_iterator<string> output(cout, " ");

	// then copy straight from file to cout
	copy(fileIter, endIter, output);

	// add an endline after
	*output = "\n";

	return 0;
}
