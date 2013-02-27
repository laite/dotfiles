// Ex 17.25: multiple inheritance

#include <iostream>
#include <string>

class X { };
class A { };
class B : public A { };
class C : private B { };
class D : public X, public C { };

int main()
{
	D *pd = new D;

	// these assignments are ok
	X *px = pd;
	C *pc = pd;

	/*
	 * these two are not, B is a private parent
	 * and A is 'behind' B, so neither of these can
	 * be accessed through derived class D
	 *
	 * B *pb = pd;
	 * A *pa = pd;
	 */

	return 0;
}
