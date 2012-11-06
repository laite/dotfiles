// Ex 7.31: read and write sales_items

#include "Ch7Headers.h"
#include "Sales_item.h"

int main()
{
	Sales_item a, b;
	cout << a.read_sales() << endl;

	a.new_sale(10, 125, "ISBN-00000001");
	a.new_sale(1, 15, "ISBN-00000001");

	b.new_sale(1, 1500, "ISBN-00000001");

	a.add(b);

	cout << a.read_sales() << endl;

	return 0;
}
