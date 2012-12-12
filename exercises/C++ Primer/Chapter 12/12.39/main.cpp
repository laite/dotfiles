// Ex 12.39: Introducing Bar

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
		static Foo barFoo;
		static int barInt;

	private:
		/* data */
};

int main()
{
	Foo myPrettyFoo(33);

	return 0;
}
