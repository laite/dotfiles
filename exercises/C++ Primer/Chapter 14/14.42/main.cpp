// Ex 14.42: conversion to bool

#include <iostream>
#include <string>
#include <vector>
#include <map>

struct Date
{
	Date(unsigned long s): sec(s) {}
	unsigned long sec;
};

class CheckoutRecord 
{
	friend std::ostream& operator<<(std::ostream &o, CheckoutRecord record);
	public:
		
		CheckoutRecord(): book_id(222255), title("title"), date_borrowed(14), date_due(15),
							borrower(std::make_pair("tina","doughnut")) { }

		// return true if borrower has a name
		operator bool() { return (borrower.first.size() != 0); }

	private:

		double book_id;
		std::string title;
		Date date_borrowed;
		Date date_due;
		std::pair<std::string, std::string> borrower;
		std::vector< std::pair<std::string, std::string>* > wait_list;
};

std::ostream& operator<<(std::ostream &o, CheckoutRecord record)
{
	o << record.book_id << ", " << record.title << ", " << record.date_borrowed.sec 
			<< ", " << record.date_due.sec << ", " << record.borrower.first << " " << record.borrower.second << ".";

	return o;
}

int main()
{
	CheckoutRecord c;

	std::cout << c << std::endl;

	// static cast is unnecessary, but elaborates the point here nicely
	if (static_cast<bool>(c))
		std::cout << "true" << std::endl;
	
	return 0;
}
