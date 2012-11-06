// Ex 9.42: read words into a stack

#include "../../helpers.h"

int main()
{
	stack<string> stringStack;
	cout << "Type some strings in wrong order." << endl;

	string s;
	while (cin >> s)
		stringStack.push(s);

	while (stringStack.empty() != true)
	{
		cout << stringStack.top();
		stringStack.pop();
	}

	cout << endl;

	return 0;
}
