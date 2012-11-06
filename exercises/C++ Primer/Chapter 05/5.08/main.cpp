// Ex 5.08: while, logical AND

#include "../Ch5headers.h"

int main()
{
	cout << "Please tell me the meaning of life, the universe and everything." << endl;

	string answer("");

	while (answer != "42" && cin >> answer)
	{
		if (answer != "42")
			cout << "nope." << endl;
		else
			cout << "You might be onto something there." << endl;
	}

	return 0;
}
