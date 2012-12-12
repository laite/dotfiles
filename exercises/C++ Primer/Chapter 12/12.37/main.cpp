// Ex 12.37: static class variables

#include "../../helpers.h"

const double kInterestRate = 0.03;

class Account {
	public:
		Account (std::string owner, double amount): _owner(owner), _amount(amount) {}
		static double rate();
		static void ChangeInterestRate(double newRate) { _interestRate = newRate; }
	private:
		std::string _owner;
		double _amount;
		static double _interestRate;
		static double InitRate() { return kInterestRate; }
};

double Account::rate()
{
	return Account::_interestRate;
}

// must declare the value for _interestRate explicitly
double Account::_interestRate = InitRate();

int main()
{

	Account firstAccount("Minna", 500.33);

	// We can change interest rate straight from class instead of class objects
	Account::ChangeInterestRate(0.5);
	Account secondAccount("Tiina", 0.44);

	cout << firstAccount.rate() << ", " << secondAccount.rate() << endl;
 
	// we can also access rate straight from the class
	// since it is defined as static function
	cout << Account::rate() << endl;

	return 0;
}
