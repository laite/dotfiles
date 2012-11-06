// Ex 8.14: opening files

#include "../Ch8Headers.h"

std::ifstream &open_file(std::ifstream &in, const string &file)
{
	in.close();
	in.clear();

	in.open(file.c_str());

	return in;
}

std::ofstream &open_file(std::ofstream &out, const string &file)
{
	// close & clear in case there is an existing file open within stream
	out.close();
	out.clear();

	out.open(file.c_str());

	return out;
}

int main()
{
	std::ifstream myInput;

	cout << "Please give a file to read!" << endl;

	string inputFile;
	cin >> inputFile;

	if (!open_file(myInput, inputFile).good())
	{
		cout << "There's no file like that!" << endl;
		return -1;
	}

	string s;
	while (myInput>> s)
		cout << s << endl;

	myInput.close();

	return 0;
}
