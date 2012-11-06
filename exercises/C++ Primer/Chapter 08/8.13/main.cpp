// Ex 8.13: opening file for output

#include "../Ch8Headers.h"

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
	std::ofstream myOut;
	
	open_file(myOut, "output");

	myOut << "boobs" << endl;

	myOut.close();

	return 0;
}
