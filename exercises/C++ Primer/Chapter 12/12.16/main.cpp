// Ex 12.16: class scope

#include "../../helpers.h"

class Testclass
{
	public:
		typedef std::string::size_type index;
		index Function();
};

int main()
{

	return 0;
}
