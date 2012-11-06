// Ex 7.20: rewriting recursiveFactorial as iterative

#include "../Ch7Headers.h"

// calculate val!, which is 1*2 *3 ... * val
int recursiveFactorial(int val)
{
	if (val > 1)
		return recursiveFactorial(val-1) * val;

	return 1;
}

int factorial(int val)
{
	int result = val;
	while (--val)
		result *= val;


	return result;
}

int main()
{
	cout << "factorial of 10 is " << factorial(10) << endl;
	cout << "factorial of 10 (recursively) is " << recursiveFactorial(10) << endl;

	return 0;
}
