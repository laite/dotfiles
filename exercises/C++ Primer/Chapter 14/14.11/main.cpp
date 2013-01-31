// Ex 14.11: ...and inputs
// Add operator >> to Ex 14.07

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
	friend std::ostream& operator<<(std::ostream &o, const CheckoutRecord &record);
	friend std::istream& operator>>(std::istream &i, CheckoutRecord &record);

	public:
		
		CheckoutRecord(): book_id(222255), title("title"), date_borrowed(14), date_due(15),
							borrower(std::make_pair("tina","doughnut")) { }
	private:

		double book_id;
		std::string title;
		Date date_borrowed;
		Date date_due;
		std::pair<std::string, std::string> borrower;
		std::vector< std::pair<std::string, std::string>* > wait_list;
};

std::ostream& operator<<(std::ostream &o, const CheckoutRecord &record)
{
	o << record.book_id << ", " << record.title << ", " << record.date_borrowed.sec 
			<< ", " << record.date_due.sec << ", " << record.borrower.first << " " << record.borrower.second << ".";

	return o;
}

std::istream& operator>>(std::istream &i, CheckoutRecord &record)
{
	i >> record.book_id >> record.title >> record.date_borrowed.sec 
			>> record.date_due.sec >> record.borrower.first >> record.borrower.second;

	if (!i) // if something went wrong
		record = CheckoutRecord();
	
	return i;
}

int main()
{
	CheckoutRecord c;

	std::cout << c << std::endl;
	std::cin >> c;
	std::cout << c << std::endl;
	
	return 0;
}
