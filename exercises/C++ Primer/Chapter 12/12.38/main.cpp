// Ex 12.38: defining Foo

#include "../../helpers.h"

class Foo {
	public:
		Foo (int m): _member(m) {}

		int GiveMember() { return _member; }
	private:
		int _member;
};
int main()
{
	Foo myPrettyFoo(33);

	return 0;
}
