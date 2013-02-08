// Ex 15.14: constructors between classes

#include <iostream>
#include <string>

class Item_base 
{
	public:

		Item_base(std::string i = "", double p = 3.0): price(p), isbn(i) { }

		virtual double net_price(std::size_t n) { return n * price; }
		virtual ~Item_base() { };

	protected:

		double price;
		std::string isbn;
};

class Bulk_item : public Item_base 
{
	public:

		Bulk_item(std::string book = "", double p = 3.0, double disc = 0.25, std::size_t qnt = 10): 
			Item_base(book, p), discount(disc), min_qnt(qnt) {}
		double net_price(std::size_t n);

	private:

		std::size_t min_qnt;
		double discount;
		
};

double Bulk_item::net_price(size_t n)
{
	if (n >= min_qnt)
		return n * (1 - discount) * price;
	else
		return n * price;
}

int main()
{
	// basic item with no discounts
	Item_base a;

	// create bulk_item which costs 49.99, but with three or more items 
	// shopper gets 33% discount
	Bulk_item b("1-1-111", 49.99, 0.33, 3);

	// create bulk item with default arguments
	Bulk_item c;

	std::cout << a.net_price(4) << std::endl;
	std::cout << b.net_price(4) << std::endl;
	std::cout << c.net_price(4) << std::endl;

	return 0;
}
