// Ex 13.26: changing 13.24 to valuelike approach of pointer management

#include <iostream>

class HasPointer 
{
	public:

		/*
		 *  Constructors and Destructors
		 */

		// New HasPointer creates a UseCount class item for holding the pointer
		HasPointer(int &p, int v): _pointer(new int(p)), _value(v) { std::cout << "New HasPointer appears!" << std::endl; }

		// Copy construction
		HasPointer(const HasPointer&);

		// assignment operator
		HasPointer& operator=(const HasPointer&);

		// Basic Destructor
		~HasPointer();

		/*
		 *  Getters
		 */

		int *GetPointer() const { return _pointer; }
		int GetInt() const { return _value; }
		int GetPointerValue() const { return *_pointer; }
		
		/*
		 *  Setters
		 */

		void SetPointer(int *p) { _pointer = p; }
		void SetInt(int v) { _value = v; }
		void SetPointerValue(int v) { *_pointer = v; }
		
	private:
		
		/*
		 *  Private variables
		 */

		int _value;
		int *_pointer;
		
};

HasPointer::HasPointer(const HasPointer &rhsHasPointer):
	_value(rhsHasPointer._value)
{
	std::cout << "Copy Constructed HasPointer." << std::endl;
	
	_pointer = new int(*rhsHasPointer._pointer);
}

HasPointer& HasPointer::operator=(const HasPointer &rhsHasPointer)
{
	if (&rhsHasPointer == this)
		std::cout << "Assigning to itself (not to worry, though)!" << std::endl;

	// only then assign the values
	_value = rhsHasPointer._value;
	*_pointer = *rhsHasPointer._pointer;
}

HasPointer::~HasPointer()
{
	delete _pointer;
}

int main()
{
	
	/*
	 *  Initialize some test variables
	 */
	
	int i = 42, j = 24;
	HasPointer classThatHasPointer(i, 42);
	HasPointer anotherClassThatHasPointer(j, 24);
	HasPointer copyCat = classThatHasPointer;
	
	// opposed to 13.20 and 13.24, copyCat's pointer does not change
	// since each HasPointer has its very own pointer
	std::cout << copyCat.GetPointerValue() << std::endl;
	classThatHasPointer.SetPointerValue(0);
	std::cout << copyCat.GetPointerValue() << std::endl;

	// assign new values to classThatHasPointer
	classThatHasPointer = anotherClassThatHasPointer;
	std::cout << classThatHasPointer.GetPointerValue() << std::endl;



	return 0;
}
