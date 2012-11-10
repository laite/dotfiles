// Ex 12.03: constructor for Person

#include "../../helpers.h"

class Person 
{
	public:
		// getters
		string getName() const {
			return _name;
		}
		string getAddress() const { 
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

	cout << masa.getName() << "@" << masa.getAddress() << endl;

	return 0;
}
