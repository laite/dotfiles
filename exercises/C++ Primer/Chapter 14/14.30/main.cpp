// Ex 14.30: array of screens

#include <iostream>
#include <string>
#include <stdexcept>

class CheckedPtr;

class Holder 
{
	friend class CheckedPtr;

	public:

		Holder(int *v): value(v) { }

		int* GetValues() { return value; }

	private:

		int *value;		
};

class CheckedPtr 
{
	public:

		CheckedPtr(Holder *b, Holder *e): beg(b), end(e), curr(b) { }

		// prefix increment/decrement
		CheckedPtr& operator++();
		CheckedPtr& operator--();

		// postfix increment/decrement
		CheckedPtr operator++(int);
		CheckedPtr operator--(int);

		// overloaded subscript
		Holder& operator[](const unsigned int);
		const Holder& operator[](const unsigned int) const;

		// dereference and arrow
		Holder& operator*() { return *curr; }
		Holder* operator->() { return curr; }

		// equality
		bool operator==(const CheckedPtr&);
		bool operator!=(const CheckedPtr&);

	private:

		Holder *beg; 	// begin index of array
		Holder *curr; 	// current position
		Holder *end; 	// one past end of array
};

bool CheckedPtr::operator==(const CheckedPtr &rhsItem)
{
	return (beg == rhsItem.beg && end == rhsItem.end);
}

bool CheckedPtr::operator!=(const CheckedPtr &rhsItem)
{
	return !(*this == rhsItem);
}

Holder& CheckedPtr::operator[](const unsigned int i)
{
	return *(beg+i);
}

const Holder& CheckedPtr::operator[](const unsigned int i) const
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
	int arrayOfInt[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 90 };
	int arrayOfInt2[] = { -20, 56, 57, 58, 59, 60, 61, 62, 63, 64, 145 };
	int arrayOfInt3[] = { -10, -11, -2, -3, -4, -5, -6, -7, -8, -9, -90 };
	Holder arrayOfHolders[] = { Holder(arrayOfInt), Holder(arrayOfInt2), Holder(arrayOfInt3) };

	// end point is one-past the array
	CheckedPtr cPtr(arrayOfHolders, arrayOfHolders+3);

	std::cout << (cPtr->GetValues()[5]) << std::endl;
	cPtr++;
	std::cout << ((*cPtr++).GetValues()[5]) << std::endl;
	std::cout << ((*cPtr).GetValues()[5]) << std::endl;

	return 0;
}
