// Ex 13.14: verbal examples about constructors, copy constructors and destructors

#include "../../helpers.h"

class Example
{
	public:
		Example();
		~Example();
		Example(const Example&);
	private:
};

Example::Example()
{
	cout << "Example::Example()" << endl;
}

Example::Example(const Example &e)
{
	cout << "Example::Example(const Example &e)" << endl;
}

Example::~Example()
{
	cout << "Example::~Example()" << endl;
}

Example global;

int main()
{
	Example e[] = { Example(), Example() };
	{
		Example e2 = e[1];
		Example *e3 = &e2, *e4 = &global; 
	}

	Example e5;
	

	return 0;
}
