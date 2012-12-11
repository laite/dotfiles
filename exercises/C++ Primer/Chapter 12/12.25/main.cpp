// Ex 12.25: cin as a default argument

#include "../../helpers.h"

class Sales_item
{
	public:
		Sales_item(istream &is = cin): _inputStream(is) {}
	private:
		istream &_inputStream;
};

int main()
{
	// both Sales_items have cin as their _inputStream
	Sales_item inclusive, exclusive(cin);

	return 0;
}
