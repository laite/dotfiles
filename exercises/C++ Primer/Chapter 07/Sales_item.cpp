// Sales_item.cpp

#include "Ch7Headers.h"
#include "Sales_item.h"

// return avg_price zero if there is no items sold yet
double Sales_item::avg_price() const
{
	if (units_sold)
		return (revenue/units_sold);
	else
		return 0;
}

bool Sales_item::same_isbn(const Sales_item &rhs) const
{
	return isbn == rhs.isbn;
}
