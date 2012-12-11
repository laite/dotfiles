// Ex 12.

#include "../../helpers.h"

class Sales_item;
Sales_item add(Sales_item s1, Sales_item s2);

class Sales_item
{
	friend Sales_item add(Sales_item s1, Sales_item s2);

	public:
		Sales_item(): _myPreciousness(33) {}
		Sales_item(int prec): _myPreciousness(prec) {}

		int Out() { return _myPreciousness; }
	private:
		int _myPreciousness;
};

// add is a nonmember function which has access to Sales_item classes private members
Sales_item add(Sales_item s1, Sales_item s2)
{
	return Sales_item(s1._myPreciousness + s2._myPreciousness);
}

int main()
{
	Sales_item item1(500), item2;

	cout << add(item1, item2).Out() << endl;

	return 0;
}
