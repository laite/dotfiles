// Ex 8.08: example 8.07 with 'continue' in loop

#include "../Ch8Headers.h"

void process(string &s)
{
	cout << s << endl;

	return;
}

int main()
{
	std::ifstream input;
	vector<string> files;

	string s[] = {"1st", "erroneousfile", "2nd", "3rd"};

	for (int i = 0; i < 4; ++i)
		files.push_back(s[i]);

	vector<string>::const_iterator iter = files.begin();

	while (iter != files.end())
	{
		input.open(iter->c_str()); // how cool is this :P
		++iter;

		//if the file is not ok, we'll skip to next
		if (!input)
		{
			std::cerr << "** WARNING: Bad file name '" << (iter-1)->c_str() << "'!\n";
			continue;
		}

		string s;
		while (getline(input,s)) // read one line per loop
			process(s);

		input.close();// then close
		input.clear();// reset state to ok
	}

	return 0;
}
