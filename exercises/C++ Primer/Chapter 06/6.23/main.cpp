// Ex 6.23-6.24: handling errors, ala overflow

#include "../Ch6headers.h"

int main()
{

	/* can't seem to throw an overflow_error :(( */

	unsigned long ul = 900000000;
#ifndef NDEBUG
	std::cerr << "Error: " << __FILE__
              << " : line " << __LINE__ << endl
              << "Compiled on " << __DATE__
              << " at " << __TIME__ << endl
              << ": Length too short" << endl;
#endif
	try 
	{
		bitset<999> b(2368446743111636877331u);
		ul = b.to_ulong();
		cout << ul << endl;

		int unsigned i = 23423423423423423423424242;
		cout << i << endl;

		if (i == ul) { cout << "juu." << endl; }
	}
	catch (std::length_error err)
	{
		cout << err.what() << "ASDA" << endl;
	}
	catch (std::overflow_error err) 
	{
		cout << err.what() << endl;
	}

	return 0;
}
