// Ex 13.24: implementing UseCount class to exercise 13.20

#include <iostream>

class HasPointer;

class UseCount 
{
	friend class HasPointer;
		
	// All items in this class are private
	private:

		/*
		 *  Constructors and Assignments
		 */
		
		UseCount(int *ptr): _pointer(ptr), _useCount(1) {}

		~UseCount() { std::cout << "Destroying UseCounter" << std::endl; }
		
		/*
		 *  Variables
		 */
		
		size_t _useCount;
		int *_pointer;
		
};

class HasPointer 
{
	public:

		/*
		 *  Constructors and Destructors
		 */

		// New HasPointer creates a UseCount class item for holding the pointer
		HasPointer(int *p, int v): _pointerHold(new UseCount(p)), _value(v) { std::cout << "New HasPointer appears!" << std::endl; }

		// Copy construction
		HasPointer(const HasPointer&);

		// assignment operator
		HasPointer& operator=(const HasPointer&);

		// Basic Destructor
		~HasPointer();

		/*
		 *  Getters
		 */

		int *GetPointer() const { return _pointerHold->_pointer; }
		int GetInt() const { return _value; }
		int GetPointerValue() const { return *(_pointerHold->_pointer); }
		
		/*
		 *  Setters
		 */

		void SetPointer(int *p) { _pointerHold->_pointer = p; }
		void SetInt(int v) { _value = v; }
		void SetPointerValue(int v) { *(_pointerHold->_pointer) = v; }
		
	private:
		
		/*
		 *  Private variables
		 */

		int _value;
		UseCount *_pointerHold;
		
};

HasPointer::HasPointer(const HasPointer &rhsHasPointer):
	_pointerHold(rhsHasPointer._pointerHold),
	_value(rhsHasPointer._value)
{
	++_pointerHold->_useCount;
	std::cout << "Copy Constructed HasPointer." << std::endl;
	
}

HasPointer& HasPointer::operator=(const HasPointer &rhsHasPointer)
{
	if (&rhsHasPointer == this)
		std::cout << "Assigning to itself (not to worry, though)!" << std::endl;

	// increase useCount on right-, decrease on left hand side
	++rhsHasPointer._pointerHold->_useCount;
	if (--_pointerHold->_useCount == 0)
		delete _pointerHold;

	// only then assign the values
	_value = rhsHasPointer._value;
	_pointerHold = rhsHasPointer._pointerHold;
}

HasPointer::~HasPointer()
{
	if (--_pointerHold->_useCount == 0)
	{
		std::cout << "Last instance of pointerhold down." << std::endl;
		delete _pointerHold;
	}
}

int main()
{
	
	/*
	 *  Initialize some test variables
	 */
	
	int i = 42, j = 24;
	HasPointer classThatHasPointer(&i, 42);
	HasPointer anotherClassThatHasPointer(&j, 24);
	HasPointer copyCat = classThatHasPointer;
	
	// show that copyCat truly points to same item than classThatHasPointer
	std::cout << copyCat.GetPointerValue() << std::endl;
	classThatHasPointer.SetPointerValue(0);
	std::cout << copyCat.GetPointerValue() << std::endl;

	// assign new values to classThatHasPointer
	classThatHasPointer = anotherClassThatHasPointer;
	std::cout << classThatHasPointer.GetPointerValue() << std::endl;



	return 0;
}
