// Ex 12.06: struct/class

#include "../../helpers.h"

// struct is exactly same as class, except it's default assign class is "public"
struct Helper {
	string name;
	string address;
};

class SomeClass {
	public:
		typedef Helper keeper;

		keeper dataKeeper;

		void EchoData() {
			cout << "Keeper \"" << dataKeeper.name << "\" lives at " << dataKeeper.address << endl;
		}
};

int main()
{
	SomeClass example;
	SomeClass::keeper guard = { "Guard", "East Tower" };

	// we could also set example.dataKeeper.name = "Guard"
	example.dataKeeper = guard;
	example.EchoData();

	return 0;
}
