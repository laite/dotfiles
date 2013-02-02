// Ex 14.14: assignment operator

#include <iostream>
#include <string>

class MyClass 
{
	friend MyClass operator+(const MyClass& lhs, const MyClass& rhs);
	friend std::ostream& operator<<(std::ostream &out, const MyClass &item);

	public:

		MyClass(): a(10), b("str"), c(12.4) { }
		MyClass(int i, std::string s, double d): a(i), b(s), c(d) { }

		MyClass& operator+=(const MyClass& rhsItem);

		MyClass& operator=(std::string);

	private:

		int a;
		std::string b;
		double c;
};

// non-member operator, returns new instance of MyClass
MyClass
operator+(const MyClass& lhs, const MyClass& rhs)
{
	std::cout << "** operator + **" << std::endl;
	MyClass result(lhs);

	result.a += rhs.a;
	result.b += rhs.b;
	result.c += rhs.c;

	return result;
}

// member operator, returns reference to (implicit) lhs
MyClass&
MyClass::operator+=(const MyClass& rhsItem)
{
	std::cout << "** operator += **" << std::endl;
	*this = *this + rhsItem;

	return *this;
}

std::ostream&
operator<<(std::ostream &out, const MyClass &item)
{
	out << item.a << ", " << item.b << ", " << item.c;

	return out;
}

MyClass&
MyClass::operator=(std::string newString)
{
	this->b = newString;

	return *this;
}

int
main()
{

	MyClass m;
	MyClass n(14,"that",11.11);

	std::cout << "m: " << m << std::endl;
	std::cout << "n: " << n << std::endl;

	m += n;

	// assign new string value to class item
	m = "new string";

	std::cout << "m: "<< m << std::endl;

	return 0;
}
