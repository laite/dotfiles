// Ex 12.23: classes without constructors

#include "../../helpers.h"

class NoDefault 
{
	public:
		NoDefault(int i): _ival(i) {}

		int GetVal();
	private:
		const int _ival;
};

int NoDefault::GetVal()
{
	return this->_ival;
}

class C
{
	public:
		// NoDefault has no default constructor, so we must initialize it explicitly!
		C(): _nn(420) {}
		C(int c): _nn(c) {}
	private:
		NoDefault _nn; 
};

int main()
{
	C c, d(50);
	NoDefault nd(12); 

	cout << "nd returns " << nd.GetVal() << endl;

	return 0;
}
