// Ex 15.20: copy control and assignments of classes

#include <iostream>
#include <string>

class Item_base 
{
	public:

		Item_base(std::string i = "", double p = 3.0): price(p), isbn(i) { }

		// copy constructor
		Item_base(const Item_base &i)  { price = i.price; isbn = i.isbn; std::cout << "Item_base(const &Item_base)" << std::endl; }
		// assign operator
		Item_base& operator=(const Item_base &i) { price = i.price; isbn = i.isbn; std::cout << "Item_base::operator=" << std::endl; }

		virtual double net_price(std::size_t n) { return n * price; }
		virtual ~Item_base() { std::cout << "Item_base destructor" << std::endl; };

	protected:

		double price;
		std::string isbn;
};

class Bulk_item : public Item_base 
{
	public:

		Bulk_item(std::string book = "", double p = 3.0, double disc = 0.25, std::size_t qnt = 10): 
			Item_base(book, p), discount(disc), min_qnt(qnt) {}

		// copy constructor
		Bulk_item(const Bulk_item &i): Item_base(i)  { min_qnt = i.min_qnt; discount = i.discount; std::cout << "Bulk_item(const &Bulk_item)" << std::endl; }
		// assign operator
		Bulk_item& operator=(const Bulk_item &i) { Item_base::operator=(i); min_qnt = i.min_qnt; discount = i.discount; std::cout << "Bulk_item::operator=" << std::endl; }

		double net_price(std::size_t n);
		~Bulk_item() { std::cout << "Bulk_item destructor" << std::endl; }

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
	Item_base item_a;

	// create bulk item with default arguments
	Bulk_item bulk_a;

	// create bulk_item which costs 49.99, but with three or more items 
	// shopper gets 33% discount
	Bulk_item bulk_b("1-1-111", 49.99, 0.33, 3);

	std::cout << item_a.net_price(4) << std::endl;
	std::cout << bulk_a.net_price(4) << std::endl;
	std::cout << bulk_b.net_price(4) << std::endl;

	bulk_a = bulk_b;
	std::cout << bulk_a.net_price(4) << std::endl;

	std::cout << " *** divider *** " << std::endl;

	// this calls Item_base copy constructor by converting Bulk_item b into a reference
	// to Item_base as a parameter
	Item_base item_b(bulk_a);
	std::cout << item_b.net_price(4) << std::endl;

	Bulk_item bulk_c(bulk_a);
	std::cout << bulk_c.net_price(4) << std::endl;

	return 0;
}
