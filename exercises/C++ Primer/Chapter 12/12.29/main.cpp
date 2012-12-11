// Ex 12.29: null_isbn and constructors

#include "../../helpers.h"

class MyTest
{
	public:
		explicit MyTest(string inputString): _exampleString(inputString) {}

		void PrintOut() { cout << _exampleString << endl;}
	private:
		string _exampleString;
};

void TryThis(MyTest t)
{
	t.PrintOut();
}

int main()
{
	string nullString = "9999-9999-99";
	MyTest testObject1(nullString);

	// without 'explicit' keyword in class constructor we could use simple
	// TryThis(nullString);
	// object created as a parameter is destroyed immediately after TryThis() finishes
	TryThis(MyTest(nullString));

	return 0;
}
