// Ex 13.20: pointers in classes

#include "../../helpers.h"

class HasPointer 
{
	public:

		/*
		 *  Constructors and Destructors
		 */

		HasPointer(int *p, int v): _pointer(p), _value(v) {}

		/*
		 *  Getters
		 */

		int 
		*GetPointer() const 
			{ return _pointer; }
		int 
		GetInt() const 
			{ return _value; }
		int
		GetPointerValue() const 
			{ return *_pointer; }
		
		/*
		 *  Setters
		 */

		void
		SetPointer(int *p) 
			{ _pointer = p; }
		void
		SetInt(int v) 
			{ _value = v; }
		void
		SetPointerValue(int v) 
			{ *_pointer = v; }
		
	private:
		
		/*
		 *  Private variables
		 */

		int _value;
		int *_pointer;
		
};

int main()
{

	int i = 42;
	HasPointer classThatHasPointer(&i, 42);
	HasPointer copyCat = classThatHasPointer;

	cout << copyCat.GetPointerValue() << endl;
	classThatHasPointer.SetPointerValue(0);
	cout << copyCat.GetPointerValue() << endl;

	return 0;
}
