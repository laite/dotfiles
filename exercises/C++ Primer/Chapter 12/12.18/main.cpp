// Ex 12.18: fixing bad code (about scopes)

#include "../../helpers.h"

// really bad idea to use same names for global and class function and typedef
typedef string Type;
Type initVal();

class Exercise
{
	public:
		// ...
		typedef double Type;
	   	Type setVal(Type);
		Type initVal() {};
	private:
		int val;
};

Exercise::Type Exercise::setVal(Type parm)
{
	// parm is Exercise::Type, initVal is called from class definition
	val = parm + initVal();
}

int main()
{
	Exercise e;

	return 0;
}
