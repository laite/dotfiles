// Ex 12.21: default constructors

#include "../../helpers.h"

double d(10.0);
ifstream fileStream("someFile");

class Test
{
	public:
		Test(): _kClassName("Test"), _ival(0), _dptr(&d), _input(fileStream) {}
	private:
		const string _kClassName;
		int _ival;
		double *_dptr;
		ifstream &_input; 
};

int main()
{
	
	return 0;
}
