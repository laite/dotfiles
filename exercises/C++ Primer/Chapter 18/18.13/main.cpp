// Ex 18.13 dynamic casting
// Modified to represent ex. 18.14 (virtual inheritance)

#include <iostream>
#include <string>

class A { public: A() { } virtual ~A() { }};
class B : virtual public A { public: B() { } virtual ~B() { }};
class C : public B { public: C() { } virtual ~C() { }};
class D : public B, virtual public A { public: D() { } virtual ~D() { }};

int main()
{
	A *pa = new C;
	B *pb = dynamic_cast< B* >(pa);

	B *pb2 = new B;
	C *pc = dynamic_cast< C* >(pb2);

	A *pa2 = new D;
	B *pb3 = dynamic_cast< B* >(pa2);

	return 0;
}
