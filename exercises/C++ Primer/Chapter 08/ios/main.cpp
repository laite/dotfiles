// Ex 8.

#include "../Ch8Headers.h"
#include <stdexcept>
#include <istream>

int main()
{
	int ival;
    // read cin and test only for EOF; loop is executed even if there are other IO failures
    while (cin >> ival, !cin.eof()) {
        if (cin.bad())         // input stream is corrupted; bail out
            throw std::runtime_error("IO stream corrupted");
        if (cin.fail()) {                        // bad input
            cerr<< "bad data, try again";        // warn the user
            cin.clear(std::istream::failbit);         // reset the stream
            continue;                            // get next input
        }
        // ok to process ival
    }
	return 0;
}
