// Ex 18.17: type info

#include <iostream>
#include <string>
#include <typeinfo>

struct Base 
{
		Base() { }
		virtual ~Base() { }

		void print1() { std::cout << "base" << std::endl; }
};

struct Derived : public Base 
{
		Derived() { }
		virtual ~Derived() { }

		void print2() { std::cout << "derived" << std::endl; }
};

int main()
{
	Base *bp = new Derived;

	bp->print1();
	// bp->print2(); // error! Base has no member print2()

	if (typeid(*bp) == typeid(Derived))
		dynamic_cast<Derived*>(bp)->print2();
	else
		std::cout << "typeid mismatch" << std::endl;

	Base &br = *bp;

	if (typeid(br) == typeid(Derived))
	{
		Derived &ref = dynamic_cast<Derived&>(br);
		ref.print1();
		ref.print2();

		if (typeid(br) == typeid(*bp))
			std::cout << "br == *bp (type-wise)" << std::endl;
	}

	return 0;
}
