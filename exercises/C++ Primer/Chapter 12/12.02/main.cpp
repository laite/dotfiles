// Ex 12.02: constructor for Person

#include "../../helpers.h"

class Person 
{
	public:
		// default constructor initials empty strings
		Person(): Name(""), Address("") {}

		// constructor that takes two strings as argument
		Person(string &a, string &b): Name(a), Address(b) {}
	private:
		string Name;
		string Address;
};

int main()
{
	Person masa;

	return 0;
}
