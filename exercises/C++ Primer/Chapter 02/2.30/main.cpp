// Ex 2.30 : data members of classes

#include <iostream>

class Database
{
	public:
		std::string Address, EmployeeOrCompany;
		unsigned StudentNumber;
		long PhoneNumber;
	private:
};

int main()
{
	Database myd;
	myd.Address = "Test Street 22";
	myd.PhoneNumber = 503318181;

	std::cout << myd.Address << std::endl << myd.PhoneNumber << std::endl;
	return 0;
}
