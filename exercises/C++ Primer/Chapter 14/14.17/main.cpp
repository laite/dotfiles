// Ex 14.17: Subscript operator

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

		CheckoutRecord& operator=(const CheckoutRecord& rhsRecord);
		std::pair<std::string, std::string>& operator[](const int);
		const std::pair<std::string, std::string>& operator[](const int) const;

		void SetTitle(std::string s) { title = s; }
	private:

		double book_id;
		std::string title;
		Date date_borrowed;
		Date date_due;
		std::pair<std::string, std::string> borrower;
		std::vector< std::pair<std::string, std::string> > wait_list;
};

// our example places only title, skipping rest as trivial
CheckoutRecord& CheckoutRecord::operator=(const CheckoutRecord& rhsRecord)
{
	title = rhsRecord.title;
	
	// all the rest assignments 
	// would go here
	// and here

	return *this;
}

std::ostream& operator<<(std::ostream &o, CheckoutRecord record)
{
	o << record.book_id << ", " << record.title << ", " << record.date_borrowed.sec 
			<< ", " << record.date_due.sec << ", " << record.borrower.first << " " << record.borrower.second << ".";

	return o;
}

std::pair<std::string, std::string>& CheckoutRecord::operator[](const int i)
{
	return wait_list[i]; // no range checking is done here
}

// we have a separate function to return const reference
const std::pair<std::string, std::string>& CheckoutRecord::operator[](const int i) const
{
	return wait_list[i];
}

int main()
{
	CheckoutRecord c, d;

	std::cout << c << std::endl;

	d.SetTitle("newTitle");
	c = d;
	std::cout << c << std::endl;

	return 0;
}
