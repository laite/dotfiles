// Ex 13.12: Destructors

#include "../../helpers.h"

struct NoName
{
	public:
		// default constructor
		NoName(): pstring(new std::string()), i(0), d(0) {}
		// constructor that takes a string as an argument
		NoName(string s): pstring(new std::string(s)), i(0), d(0) {}
		// copy constructor
		NoName(const NoName &original):
		   pstring(original.pstring), i(original.i), d(original.d) {}
		// assignment operator
		NoName& operator=(const NoName &);
		// destructor
		~NoName() { cout << "destroyed." << endl; }

		// prints *pstring into stdout
		void PrintOut() { cout << *pstring << endl; }
	private:
		std::string *pstring;
		int i;
		double d;
};

NoName& NoName::operator=(const NoName &rhs)
{
	cout << "Operating!" << endl;
	pstring = rhs.pstring;
	i = rhs.i;
	d = rhs.d;
	return *this;
}

int main()
{
	NoName nn("This");
	NoName mm("That");

	nn.PrintOut();
	mm.PrintOut();
	mm = nn;
	mm.PrintOut();

	return 0;
}
