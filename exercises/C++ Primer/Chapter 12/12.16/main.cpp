// Ex 12.16: class scope

#include "../../helpers.h"

class Testclass
{
	public:
		typedef std::string::size_type index;
		index Function();
};

// we need to include scope to both the return type and name here
Testclass::index Testclass::Function()
{
	return 1;
}

int main()
{
	Testclass testObject;

	return 0;
}
