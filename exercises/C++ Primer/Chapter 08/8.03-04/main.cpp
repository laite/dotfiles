// Ex 8.03-4: streams

#include "../Ch8Headers.h"

istream &print(istream &is)
{
	try
	{
		int i;
		while (is >> i, !is.eof() && is.good())
			cout << i << endl;

		if (is.eof())
			throw std::runtime_error("Ctrl+D");
		else 
			throw std::runtime_error("something else");
	}
	catch (std::runtime_error e)
	{
		cout << "[" << e.what() << "]" << endl;
	}

	is.clear();

	return is;
}

int main()
{
	cout << "Please type some numbers [Ctrl+D ends]" << endl;

	print(print(cin));

	return 0;
}
