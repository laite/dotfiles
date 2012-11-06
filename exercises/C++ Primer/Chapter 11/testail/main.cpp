// Ex 11.

#include "../../helpers.h"

int main()
{
	list<string> stringList { "this", "that", "those", "them", "dem" };
	vector<const char*> charVector { "this", "that", "nothing", "more" };

	size_t cnt = 0;
	list<string>::iterator iter = stringList.begin();

	while ((iter = find_first_of(iter, stringList.end(), charVector.begin(), charVector.end())) != stringList.end())
	{
		++cnt;
		++iter;
	}

	cout << "cnt: " << cnt << " matches" << endl;

	string basic = string("this I know;");
	vector<string> s { "yet ", "here ", "I ", "am ", "not" };

	string result = accumulate(s.begin(), s.end(), basic);

	cout << result << endl;

	/* checking replace_copy() and back_inserter (nice!) */

	vector<string> sVec;

	// replace_copy takes five parameters: begin and end of what to copy, destination iter (here back_inserter)
	// and what should be replaced to what
	// note that without back_inserter we must have enough items allocated in sVec!
	replace_copy(stringList.begin(), stringList.end(), back_inserter(sVec), "that", "what");

	for (vector<string>::iterator i = sVec.begin(); i != sVec.end(); )
		cout << *(i++) << " ";

	cout << endl;

	return 0;
}
