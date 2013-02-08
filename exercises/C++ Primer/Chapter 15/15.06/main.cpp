// Ex 15.06: Item_base and Bulk_item

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

		Bulk_item(): discount(0.2), min_qnt(4) {}
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
	Bulk_item b;

	std::cout << b.net_price(4) << std::endl;

	return 0;
}
