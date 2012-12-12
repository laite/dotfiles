// Ex 12.41: statical functionalities, continue

#include "../../helpers.h"

class Foo {
	public:
		static int GiveMember() { return _member; }
	private:
		static int _member;
};

class Bar {
	public:
		static int FooVal() { ++callsFooVal; return _barFoo.GiveMember(); }
		static int callsFooVal;

	private:
		static Foo _barFoo;
};

int Foo::_member(20);
int Bar::callsFooVal(0);
Foo Bar::_barFoo;

int main()
{
	Foo myPrettyFoo;
	Bar mySnugglyBar;

	for (int i = 0; i < 4; i++) {
		Bar::FooVal();
	}


	cout << "Fooval's value: " << Bar::FooVal() << endl;
	cout << "callsFooVal: " << Bar::callsFooVal << endl;
	return 0;
}
