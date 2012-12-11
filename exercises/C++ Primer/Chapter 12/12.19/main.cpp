// Ex 12.19: constructors

#include "../../helpers.h"

class NoName
{
	public:
		NoName() {}
		NoName(std::string& str): pstring(&str) {}
		NoName(int i, double d): ival(i), dval(d) {}
	private:
		std::string *pstring;
		int ival;
		double dval;
};

int main()
{
	string s("bazxc");
	NoName nn(s);
	NoName id(12, 12.0);

	return 0;
}
