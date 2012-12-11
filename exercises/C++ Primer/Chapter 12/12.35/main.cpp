// Ex 12.35: friends between scopes

#include "../../helpers.h"

class Sales_item;
bool ReadStreamIntoSales_item(istream&, Sales_item&);

class Sales_item
{
	friend bool ReadStreamIntoSales_item(istream&, Sales_item&);

	public:
		Sales_item(): _myPreciousness(33) {}
		Sales_item(int prec): _myPreciousness(prec) {}

		int Out() { return _myPreciousness; }
	private:
		int _myPreciousness;
};

// this is a nonmember function which has access to Sales_item classes private members
bool ReadStreamIntoSales_item(istream& inputStream, Sales_item &destination)
{
	int userInput; // we use temporary placeholder in case the user does something silly

	cout << "Please give an integer of goodness." << endl;
	if (inputStream >> userInput) 
		destination._myPreciousness = userInput;

	return inputStream;
}

int main()
{
	Sales_item item1(500);

	if (ReadStreamIntoSales_item(cin, item1)) {
		cout << "Read successfully a new value." << endl;
	}
	else {
		cout << "Value initialization failed." << endl;
	}

	cout << item1.Out() << endl;

	return 0;
}
