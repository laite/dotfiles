// Ex 17.22: namespace overloading

#include <iostream>
#include <string>

namespace primer
{
	void compute() { std::cout << "()" << std::endl; }
	void compute(const void *v) { std::cout << "(const void *)" << std::endl; }
}

void compute(int a) { std::cout << "(int)" << std::endl; }
void compute(double a, double b = 3.14) { std::cout << "(double, double=)" << std::endl; }
void compute(char *a, char *b = 0) { std::cout << "(char *, char *=)" << std::endl; }

int main()
{
	// declaring 'using' here makes *only* compute-functions from namespace
	// available as viable candidates!
	using primer::compute;

	// this calls compute(const void*)
	// if we would've declared using primer::compute outside main scope
	// this would call compute(int)
	compute(0);

	return 0;
}
