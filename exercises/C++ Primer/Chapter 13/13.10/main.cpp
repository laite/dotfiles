// Ex 13.10: Employee class

#include "../../helpers.h"

class Employee
{
	public:
		Employee(): _name("Noname"), _ID(++runningID) {}
		Employee(const string name): _name(name), _ID(++runningID) {}
		Employee(const Employee &e) { _ID = e._ID; _name = e._name; }

		Employee& operator=(const Employee &e);

		void Out() { cout << _ID << ": " << _name << endl;}
	private:
		static int runningID;
		std::string _name;
		int _ID;
};

Employee& Employee::operator=(const Employee &e)
{
	_ID = e._ID;
	_name = e._name;

	return *this;
}

int Employee::runningID(0);

int main()
{
	Employee staff[] = { Employee(), Employee("Timi"), Employee("Joono"), Employee("Saari") };

	vector<Employee> employees(staff, staff+4);

	for (vector<Employee>::iterator iter = employees.begin(); iter != employees.end(); iter++)
		iter->Out();

	cout << "** Joono is no good!" << endl;
	cout << "** Introducing new, cheap engineer." << endl;
	Employee cheapIngenjoer("Tuomu");

	employees[2] = cheapIngenjoer;

	for (vector<Employee>::iterator iter = employees.begin(); iter != employees.end(); iter++)
		iter->Out();

	return 0;
}
