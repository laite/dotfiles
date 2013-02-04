// Ex 14.

#include <iostream>
#include <string>
#include <stdexcept>

class CheckedPtr 
{
	public:

		CheckedPtr(int *b, int *e): beg(b), end(e), curr(b) { }

		// prefix increment/decrement
		CheckedPtr& operator++();
		CheckedPtr& operator--();

		// postfix increment/decrement
		CheckedPtr operator++(int);
		CheckedPtr operator--(int);

		// overloaded subscript
		int& operator[](const unsigned int);
		const int& operator[](const unsigned int) const;

		// dereference
		int operator*() { return *curr; }

	private:

		int *beg; 	// begin index of array
		int *curr; 	// current position
		int *end; 	// one past end of array
};

int& CheckedPtr::operator[](const unsigned int i)
{
	return *(beg+i);
}

const int& CheckedPtr::operator[](const unsigned int i) const
{
	return *(beg+i);
}

CheckedPtr CheckedPtr::operator++(int)
{
	CheckedPtr old(*this);
	++*this;

	return old;
}

CheckedPtr& CheckedPtr::operator++()
{
	if (curr == end)
		throw std::out_of_range("increment over range!");

	++curr;
	return *this;
}

CheckedPtr CheckedPtr::operator--(int)
{
	CheckedPtr old(*this);
	--*this;
	return old;
}

CheckedPtr& CheckedPtr::operator--()
{
	if (curr == beg)
		throw std::out_of_range("increment below begin!");

	--curr;
	return *this;
}

int main()
{
	int arrayOfInt[] = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89 };

	// end point is one-past the array
	CheckedPtr cPtr(arrayOfInt, arrayOfInt+sizeof(arrayOfInt)/sizeof(int) + 1);

	cPtr++;

	std::cout << (*cPtr) << std::endl;

	return 0;
}
