// Ex 12.03: constructor for Person

#include "../../helpers.h"

class Person 
{
	public:
		// getters
		string GetName() const {
			return _name;
		}
		string GetAddress() const { 
			return _address;
		}

		// default constructor initials empty strings
		Person(): _name(""), _address("") {}

		// constructor that takes two (const) strings as argument
		Person(const string &name, const string &address): _name(name), _address(address) {}
	private:
		string _name;
		string _address;
};

int main()
{
	Person masa("Masa", "Mierontie");

	cout << masa.GetName() << "@" << masa.GetAddress() << endl;

	return 0;
}
