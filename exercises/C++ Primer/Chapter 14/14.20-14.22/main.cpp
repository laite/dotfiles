// Ex 14.20-14.22: ScreenPtr class, working with different operators

#include <iostream>
#include <string>

class ScreenPtr;
class WorkingClass;

/*
 *  Class definitions
 */

class Screen 
{
	public:
	private:
};

// a private class for use by ScreenPtr only
class _ScrPtr 
{
	friend class ScreenPtr;
	friend class WorkingClass;

	public:

		_ScrPtr(Screen *p): sp(p), use(1) { std::cout << "New _ScrPtr created" << std::endl; }
		~_ScrPtr();

		size_t GetUseCount() { return use; }

	private:

		Screen *sp;
		size_t use;

};

class WorkingClass 
{
	public:

		WorkingClass(ScreenPtr *s): _area(s) { std::cout << "Workin class has been created." << std::endl; }

		_ScrPtr *operator->();

	private:

		ScreenPtr *_area;
		
};

// smart pointer class
class ScreenPtr 
{
	friend class WorkingClass;

	public:

		// no default constructor, must be bound to an object
		ScreenPtr(Screen *p): ptr(new _ScrPtr(p)) { std::cout << "New ScreenPtr created" << std::endl; }

		// copy members and increment use count
		ScreenPtr(const ScreenPtr &orig): ptr(orig.ptr) { ++ptr->use; std::cout << "New ScreenPtr created from previous" << std::endl; }

		// assignment operator
		ScreenPtr& operator=(const ScreenPtr&);

		// operators to test equality and inequality
		bool operator==(const ScreenPtr&) const;
		bool operator!=(const ScreenPtr&) const;

		// if use count goes to zero, delete the _ScrPtr object
		~ScreenPtr();

	private:

		_ScrPtr *ptr;
};

/*
 *  Functions
 */

_ScrPtr::~_ScrPtr()
{
	std::cout << "_ScrPtr destroyed" << std::endl;

	delete sp;
}

_ScrPtr* WorkingClass::operator->()
{
	return _area->ptr;
}

ScreenPtr::~ScreenPtr()
{ 
	std::cout << "ScreenPtr destroyed" << std::endl;

	if (--ptr->use == 0)
		delete ptr; 
}

ScreenPtr& ScreenPtr::operator=(const ScreenPtr &rhsPointer)
{
	std::cout << "Assigning ScreenPtrs" << std::endl;

	// we delete ptr if this was last one using it
	if (--ptr->use == 0)
		delete ptr; 

	// switch pointer to rhs.ptr and increase its use counter
	ptr = rhsPointer.ptr;
	++ptr->use;

	return *this;
}

bool ScreenPtr::operator==(const ScreenPtr &rhsItem) const
{
	return (this->ptr == rhsItem.ptr);
}

bool ScreenPtr::operator!=(const ScreenPtr &rhsItem) const
{
	return !(*this == rhsItem);
}

int main()
{
	Screen *s = new Screen();
	ScreenPtr screenPointer(s), screenPointer2(screenPointer);
	ScreenPtr differentScreenPointer(s);

	screenPointer = differentScreenPointer;

	WorkingClass Farmer(&screenPointer);

	// overloaded -> operator returns pointer to WorkingClass._area.ptr
	// so we can call function from _ScrPtr like this
	std::cout << Farmer->GetUseCount() << std::endl;

	// our equality operators can now be used to see whether ptr of classes points to same memory
	// These both return 'true'
	std::cout << (screenPointer == differentScreenPointer) << std::endl;
	std::cout << (screenPointer != screenPointer2) << std::endl;

	return 0;
}
