// Ex 12.

#include "../../helpers.h"

class Sales_item
{
	public:
		// explicit inline; since this function is defined inside class
		// it would be (implicit) inline anyway
		inline double avg_price() {
			return (static_cast<double>(_revenue) / _sales);
		}

		Sales_item(): _revenue(10), _sales(3) {}

	private:
		short _revenue;
		short _sales;
};

int main()
{
	Sales_item item;

	cout << "Avg sale today: " << item.avg_price() << endl;

	return 0;
}
