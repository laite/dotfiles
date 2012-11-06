// 7.31: Sales_item.cpp

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

bool Sales_item::new_sale(const short units, const double income, const std::string new_isbn)
{
	if (isbn != "" && isbn != new_isbn)
		return false; // no sale unless isbn matches

	isbn = new_isbn;
	units_sold += units;
	revenue += income;

	return true;
}

std::string Sales_item::read_sales() const
{
	std::string s;
	s = "ISBN: " + isbn + "\nSold: " + to_string(units_sold) + "\nRevenue: " + to_string(revenue) + " (" + to_string(avg_price()) + ")";

	return s;
}

bool Sales_item::add(Sales_item &other)
{
	if (isbn != other.isbn)
		return false;

	units_sold += other.units_sold;
	revenue += other.revenue;

	return true;
}

// private method to switch number to string (doesn't really belong here, but for the sake of an example...)
std::string Sales_item::to_string(double i) const
{
	std::stringstream ss;
	ss << i;
	return ss.str();
}
