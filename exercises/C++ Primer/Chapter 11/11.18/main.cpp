// Ex 11.18: evening the odds

#include "../../helpers.h"

bool isEven(const int &i)
{
	return ((i%2)==0);
}

int main()
{
	// create iterators for cin and an empty iter for EOF (or bad cin)
	istream_iterator<int> input(cin), inputEOF;
	// we'll send output straight to files 'odd' and 'even'
	// using ostream_iterators (separate values by newline)
	ofstream file_odd("odd"), file_even("even");
	ostream_iterator<int> outputOdd(file_odd, "\n"), outputEven(file_even, "\n");

	while (input != inputEOF)
	{
		// note that input is incremented in either case (important!)
		if (isEven(*input))
			*outputEven++ = *input++;
		else
			*outputOdd++ = *input++;
	}

	return 0;
}
