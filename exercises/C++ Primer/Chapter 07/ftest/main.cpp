// testing

#include "../Ch7Headers.h"

// we only 'borrow' s for this instead of creating new presentation
int count(const string &s, char c)
{
	int count = 0;
	for (string::size_type i = 0; i != s.size(); ++i)
	{
		if (s[i] != c)
			count++;
	}

	return count;
}

string &ChangeValue(string &s, wchar_t which, wchar_t toWhat)
{
	for (string::size_type i = 0; i != s.size(); ++i)
		if (s[i] == which)
			s[i] = toWhat;

	cout << "changed string equals: " << s << endl;

	return s;
}

int main()
{
	string s("abracadabra");
	cout << count(s,'a') << endl;

	ChangeValue(s, 'a', 'w') = "abracadabra!";
	cout << "Meanwhile, s: " << s << endl;

	const wchar_t *myWideText = L"æbæcuß!";
	std::wcout << myWideText << endl;

	wchar_t example[] = L"\x043B";
	std::wcout << example << endl;

	wchar_t a = L'€';
	std::wcout << a;

	return 0;
}
