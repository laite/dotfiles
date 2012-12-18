// Ex 13.04: defining copy constructors explicitly

#include "../../helpers.h"

struct NoName
{
		NoName(): pstring(new std::string()), i(0), d(0) {}
		NoName(const NoName &original):
		   pstring(original.pstring), i(original.i), d(original.d) {}
	private:
		std::string *pstring;
		int i;
		double d;
};

int main()
{
	NoName nn = NoName();

	return 0;
}
