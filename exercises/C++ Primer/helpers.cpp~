// helpers.cpp

#include "helpers.h"

// definitions 
void PrintVector(vector<string> &stringVector, bool multiLine, string separator);
void PrintVector(vector<int> &intVector, bool multiLine, string separator);

void PrintList(list<int> &intList, bool multiLine, string separator);
void PrintList(list<string> &stringList, bool multiLine, string separator);

void PopulateIntVector(vector<int> &intVector, unsigned amount, unsigned max);
void PopulateIntVector(vector<int> &intVector, int *begin, int *end);

ifstream& open_file(ifstream &in, const string &file);

// declarations
void PopulateIntVector(vector<int> &intVector, unsigned amount, unsigned max)
{
	while (amount--)
		intVector.push_back(rand()%max);

	return;
}

void PopulateIntVector(vector<int> &intVector, int *begin, int *end)
{
	intVector.insert(intVector.begin(), begin, end);

	return;
}

void PrintVector(vector<int> &intVector, bool multiLine, string separator)
{
	if (!intVector.size())
		return;

	vector<int>::const_iterator iter = intVector.begin();

	while (iter != intVector.end())
	{
		cout << *iter++;

		if ((!multiLine) && (iter != intVector.end()))
			cout << separator;
		else 
			cout << endl;
	}
			
	return;
}

void PrintVector(vector<string> &stringVector, bool multiLine, string separator)
{
	if (!stringVector.size())
		return;

	vector<string>::const_iterator iter = stringVector.begin();

	while (iter != stringVector.end())
	{
		cout << *iter++;

		if ((!multiLine) && (iter != stringVector.end()))
			cout << separator;
		else 
			cout << endl;
	}
			
	return;
}

void PrintList(list<string> &stringList, bool multiLine, string separator)
{
	if (!stringList.size())
		return;

	list<string>::const_iterator iter = stringList.begin();

	while (iter != stringList.end())
	{
		cout << *iter++;

		if ((!multiLine) && (iter != stringList.end()))
			cout << separator;
		else 
			cout << endl;
	}
			
	return;
}

void PrintList(list<int> &intList, bool multiLine, string separator)
{
	if (!intList.size())
		return;

	list<int>::const_iterator iter = intList.begin();

	while (iter != intList.end())
	{
		cout << *iter++;

		if ((!multiLine) && (iter != intList.end()))
			cout << separator;
		else 
			cout << endl;
	}
			
	return;
}

// opens in binding it to the given file
ifstream& open_file(ifstream &in, const string &file)
{
	in.close();     // close in case it was already open
	in.clear();     // clear any existing errors

	// if the open fails, the stream will be in an invalid state
	in.open(file.c_str()); // open the file we were given
	return in; // condition state is good if open succeeded
}
