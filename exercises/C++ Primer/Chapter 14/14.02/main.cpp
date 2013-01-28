// Ex 14.02: overloading operators

#include <iostream>
#include <string>

class Item 
{
	friend std::istream& operator>>(std::istream&, Item&);
	friend std::ostream& operator<<(std::ostream&, const Item&);

	public:

		Item& operator+=(const Item&);

	private:
};

std::istream& operator>>(std::istream &is, Item &item)
{

}

std::ostream& operator<<(std::ostream&, const Item&)
{
	
}

// there is no actual additions made yet (not with that class implementation...)
Item& Item::operator+=(const Item& rhsItem)
{
	std::cout << "+=" << std::endl;

	return *this;
}

Item operator+(const Item& lhsItem, const Item& rhsItem)
{
	std::cout << "+" << std::endl;

	Item result(lhsItem);
	result += rhsItem;

	return result;
}

int main()
{
	Item item, item2;

	item = item + item2;
	item += item2;

	return 0;
}
