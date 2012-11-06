// Ex 9.19: correcting bad code
// This code is really quite terrible even after fixing it:
// there are a lot of better ways to accomplish something like this
// however, this 'works'

// Original, terrible code:
//
//	vector<int>::iterator mid = iv.begin() + iv.size()/2;
//	while (vector<int>::iterator iter != mid)
//		if (iter == some_val)
//			iv.insert(iter, 2 * some_val);
//
// fixed version:
// Assuming that the point is to go through items 1..mid in vector
// and insert doubled value before specific items (if found), we'll rewrite the code
// The main problem is that 'mid' moves with every insertion

#include "../../helpers.h"

int main()
{
	srand(time(NULL));

	vector<int> iv;
	int someValue = rand()%5;
	unsigned insertions = 0;
	PopulateIntVector(iv, 10, 5);

	cout << "Original vector: " << flush;
	PrintVector(iv);
	cout << "Searching for number " << someValue << endl;

	vector<int>::iterator iter = iv.begin(), end_iter = iv.begin() + iv.size()/2;
	
	while (iter != end_iter)
	{
		if (*iter == someValue)
		{
			// insert returns newly inserted position, so we add 1 to go past it
			iter = iv.insert(iter, 2 * someValue) + 1;

			// inserting before end_iter invalidates it so we must re-valuetize
			end_iter = iv.begin() + (1+iv.size())/2;

			// if we insert at a critical point, we might have bad end_iter
			// and result in skipping it completely!
			if (end_iter <= iter)
				end_iter = iter+1; // there should always be one, since we are 'at the halfway'

			// keep note about insertions
			++insertions;
		}

		// move to next
		++iter;
	}

	if (insertions)
	{
		cout << "Made " << insertions << " insertion(s)" << endl;
		PrintVector(iv);
	}
	else
		cout << "No insertions made" << endl;

	return 0;
}
