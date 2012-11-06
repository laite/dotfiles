// Ex 9.02: vector initializers

#include "../Ch9Headers.h"

int main()
{
	vector<int> i;
	i.push_back(2);

	// i) initialize i2 as a copy of i
	vector<int> i2(i);

	// ii) initialize i3 with 10 items valued 20
	vector<int> i3(10,20);

	// iii) initialize i4 with i3's values using iters
	vector<int>::const_iterator i3iter = i3.begin();
	vector<int> i4(i3iter, i3iter+i3.size());

	// iv) initialize i5 with 5 'default ints', aka zeroes
	vector<int> i5(5);

	vector< vector<int> > vectorVector;
	vectorVector.push_back(i2);
	vectorVector.push_back(i3);
	vectorVector.push_back(i4);
	vectorVector.push_back(i5);

	// print out the values
	for (vector< vector<int> >::iterator iterVecVec = vectorVector.begin();
			iterVecVec != vectorVector.end(); ++iterVecVec)
	{
		for (vector<int>::const_iterator iter = iterVecVec->begin(); iter != iterVecVec->end(); ++iter)
		{
			cout << *iter;
			if ((iter+1) != iterVecVec->end())
				cout << ", ";
			else
				cout << endl;
		}
	}

	return 0;
}
