// Ex 15.35: Adding Sales_item and a Basket

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <set>

// set default values that are used in all constructors
const double kDiscount = 0.13;
const double kPrice = 10;
const std::string kBook = "1-1-1111";
const std::size_t kQuantity = 2;

class Item_base 
{
	public:

		Item_base(std::string i = kBook, double p = kPrice): price(p), isbn(i), inClassDebugMode(true) { }

		// copy constructor
		Item_base(const Item_base &i)  { price = i.price; isbn = i.isbn; std::cout << "Item_base(const &Item_base)" << std::endl; }
		// assign operator
		Item_base& operator=(const Item_base &i) { price = i.price; isbn = i.isbn; std::cout << "Item_base::operator=" << std::endl; }

		virtual double net_price(std::size_t n) const { return n * price; }
		virtual ~Item_base() { std::cout << "Item_base destructor" << std::endl; };

		virtual Item_base* clone() const { return new Item_base(*this); }

		virtual void debug(bool debugMode = true) const;

		std::string book() const { return isbn; }

	protected:

		double price;
		std::string isbn;

		bool inClassDebugMode;
};

// Disc_item is an ABSTRACT BASE CLASS, which allows no direct instances of itself
class Disc_item : public Item_base
{
	public:

		Disc_item(std::string book = kBook, double p = kPrice, double disc = kDiscount, std::size_t qnt = kQuantity): 
			Item_base(book, p), discount(disc), min_qnt(qnt) {}

		// copy constructor
		Disc_item(const Disc_item &i): Item_base(i)  { min_qnt = i.min_qnt; discount = i.discount; std::cout << "Disc_item(const &Disc_item)" << std::endl; }
		// assign operator
		Disc_item& operator=(const Disc_item &i) { Item_base::operator=(i); min_qnt = i.min_qnt; discount = i.discount; std::cout << "Disc_item::operator=" << std::endl; }

		// PURE VIRTUAL call
		double net_price(std::size_t) const = 0;

		void debug(bool debugMode = true) const;

	protected:

		std::size_t min_qnt;
		double discount;
		
};

class Bulk_item : public Disc_item 
{
	public:

		Bulk_item(std::string book = kBook, double p = kPrice, double disc = kDiscount, std::size_t qnt = kQuantity): 
			Disc_item(book, p, disc, qnt) {}

		// copy constructor
		Bulk_item(const Bulk_item &i): Disc_item(i)  { std::cout << "Bulk_item(const &Bulk_item)" << std::endl; }
		// assign operator
		Bulk_item& operator=(const Bulk_item &i) { Disc_item::operator=(i); std::cout << "Bulk_item::operator=" << std::endl; }

		double net_price(std::size_t n) const;
		~Bulk_item() { std::cout << "Bulk_item destructor" << std::endl; }

		Bulk_item* clone() const { return new Bulk_item(*this); }
};

class Limited_discount : public Disc_item
{
	public:

		Limited_discount(std::string book = kBook, double p = kPrice, double disc = kDiscount, std::size_t qnt = kQuantity): 
			Disc_item(book, p, disc, qnt) {}

		// copy constructor
		Limited_discount(const Limited_discount &i): Disc_item(i)  { std::cout << "Limited_discount(const &Limited_discount)" << std::endl; }
		// assign operator
		Limited_discount& operator=(const Limited_discount &i) { Disc_item::operator=(i); std::cout << "Limited_discount::operator=" << std::endl; }

		double net_price(std::size_t n) const;
		~Limited_discount() { std::cout << "Limited_discount destructor" << std::endl; }

		Limited_discount* clone() const { return new Limited_discount(*this); }

	private:

		
};

class Sales_item 
{
	public:

		// Default constructor
		Sales_item(): p(NULL), use(new std::size_t(1)) { }

		// attach handle to a copy of the Item_base object
		Sales_item(const Item_base &item): p(item.clone()), use(new std::size_t(1)) { }

		// copy control members to manage the use count and pointers
		Sales_item(const Sales_item &i): p(i.p), use(i.use) { ++*use; }

		~Sales_item() { decr_use(); }

		Sales_item& operator=(const Sales_item&);

		// member access operators
		const Item_base *operator->() const { if (p) return p; else throw std::logic_error("unbound Sales item"); }
		const Item_base &operator*() const { if (p) return *p; else throw std::logic_error("unbound Sales item"); }

	private:

		Item_base *p;
		
		std::size_t *use;

		void decr_use() { if (--*use == 0) { delete p; delete use; } }
};

// compare function used in basket
inline bool
compare(const Sales_item &lhs, const Sales_item &rhs)
{
	return lhs->book() < rhs->book();
}

class Basket 
{
	typedef bool (*Comp)(const Sales_item&, const Sales_item&);

	public:

		typedef std::multiset<Sales_item, Comp> set_type;
		typedef set_type::size_type size_type;
		typedef set_type::const_iterator const_iter;

		Basket(): items(compare) { }

		void add_item(const Sales_item &item) { items.insert(item); }

		size_type size(const Sales_item &i) const { return items.count(i); }

		double total() const;

	private:

		std::multiset<Sales_item, Comp> items;
		
};

Sales_item& Sales_item::operator=(const Sales_item &rhs)
{
	++*rhs.use;
	decr_use();
	p = rhs.p;
	use = rhs.use;
	return *this;
}

void Item_base::debug(bool debugMode) const
{
	if ((!debugMode) || (!inClassDebugMode))
		return;

	std::cout << "*Item_base debug*" << std::endl << "Price: " << price << ", isbn: " << isbn << std::endl;
}

void Disc_item::debug(bool debugMode) const
{
	if ((!debugMode) || (!inClassDebugMode))
		return;

	std::cout << "*Disc_item debug*" << std::endl << "price: " << price << ", isbn: " << isbn << std::endl;
	std::cout << "min_qnt: " << min_qnt << ", discount: " << discount << std::endl;
}

// Limited discount gives discount *after* min_qnt
double Bulk_item::net_price(size_t n) const
{
	if (n >= min_qnt)
		return n * (1 - discount) * price;
	else
		return n * price;
}

// Limited discount gives discount *up to* min_qnt
double Limited_discount::net_price(size_t n) const
{
	if (n <= min_qnt)
		return n * (1 - discount) * price;
	else
		return n * price;
}

double Basket::total() const
{
	double sum = 0.0, current = 0.0;

	for (const_iter iter = items.begin(); iter != items.end();
			iter = items.upper_bound(*iter))
	{
		current = (*iter)->net_price(items.count(*iter));
		sum += current;
		std::cout << "+" << current << std::endl;
	}

	return sum;
}

int main()
{
	Bulk_item bulk_a("1-a");
	Bulk_item bulk_b("1-b");
	Bulk_item bulk_c("1-c");
	Limited_discount limited_a("2-a");
	Limited_discount limited_b("2-b");
	Limited_discount limited_c("2-c");

	Sales_item s(bulk_a);
	Sales_item s2(bulk_b);
	Sales_item s3(bulk_c);
	Sales_item s4(limited_a);
	Sales_item s5(limited_b);
	Sales_item s6(limited_c);

	Basket basket;

	basket.add_item(s);
	basket.add_item(s2);
	basket.add_item(s2);
	basket.add_item(s2);
	basket.add_item(s2);
	basket.add_item(s2);
	basket.add_item(s2);
	basket.add_item(s3);
	basket.add_item(s4);
	basket.add_item(s4);
	basket.add_item(s4);
	basket.add_item(s4);
	basket.add_item(s4);
	basket.add_item(s4);
	basket.add_item(s5);
	basket.add_item(s5);
	basket.add_item(s5);
	basket.add_item(s6);

	std::cout << "*** TOTAL " << basket.total() << "e ***" << std::endl;

	return 0;
}
