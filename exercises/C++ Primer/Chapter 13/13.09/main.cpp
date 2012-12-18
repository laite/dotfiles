// Ex 13.09: assignment operation

#include "../../helpers.h"

struct NoName
{
	public:
		NoName(): pstring(new std::string()), i(0), d(0) {}
		NoName(string s): pstring(new std::string(s)), i(0), d(0) {}
		NoName(const NoName &original):
		   pstring(original.pstring), i(original.i), d(original.d) {}
		NoName& operator=(const NoName &);
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
