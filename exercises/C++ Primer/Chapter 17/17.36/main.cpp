// Ex 17.36: multiple inheritance, constructors

#include <iostream>
#include <string>

struct Base
{
	Base() { }
	Base(std::string s): name(s) { }
	Base(const Base&): name("copy") { }

	std::string name;
};

struct Derived1 : virtual public Base
{
	Derived1() { }
	Derived1(std::string s): Base(s) { }
	Derived1(Derived1 &d): Base(d) { }
};

struct Derived2 : virtual public Base
{
	Derived2() { }
	Derived2(std::string s): Base(s) { }
	Derived2(Derived2 &d): Base(d) { }
};

struct MI : public Derived1, public Derived2
{
	MI(std::string s): Base(s) { }
	MI(MI& m): Base(m), Derived1(m), Derived2(m) { }
};

int main()
{
	// m2 gets name "copy" from copy constructor in Base class
	MI m("test"), m2(m);

	std::cout << m.name << std::endl;
	std::cout << m2.name << std::endl;

	return 0;
}
