// Ex 11.04: double confusion

#include "../../helpers.h"

inline double leikit() { return -12.0; }

int main()
{
	double dick = 12 + leikit();
	vector<double> dVec;

	for (vector<double>::size_type i = 0; i != 10; ++i)
		dVec.push_back(i/3.2);

	// accumulate calculates with int values, since 0 is an int
	cout << "with int values: " << accumulate(dVec.begin(), dVec.end(), 0) << endl;

	// dick is also zero (0), but it's type is double - accumulate(..) calculates with double values
	cout << "with double values: " << accumulate(dVec.begin(), dVec.end(), dick) << endl;

	return 0;
}
