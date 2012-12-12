// Ex 12.40: statical functionalities

#include "../../helpers.h"

class Foo {
	public:
		Foo (int m): _member(m) {}

		int GiveMember() { return _member; }
	private:
		int _member;
};

class Bar {
	public:
		static int FooVal() { ++callsFooVal; return _barFoo.GiveMember(); }
		static int callsFooVal;

	private:
		static Foo _barFoo;
};

int Bar::callsFooVal(0);
Foo Bar::_barFoo(7);

int main()
{
	Foo myPrettyFoo(33);
	Bar mySnugglyBar;

	for (int i = 0; i < 4; i++) {
		Bar::FooVal();
	}


	cout << "Fooval's value: " << Bar::FooVal() << endl;
	cout << "callsFooVal: " << Bar::callsFooVal << endl;
	return 0;
}
