// Ex 15.

#include <iostream>
#include <string>
#include <fstream>

#include "query.h"

const std::string DATAFILE("data");

int main()
{
	TextQuery t;
	std::ifstream f(DATAFILE.c_str());
	t.read_file(f);
	f.close();

	Query q("fiery"), q2("beautiful"), q3("her");
	Query final = (q & q2) | q3;

	std::set<TextQuery::line_no> s = final.eval(t);

	std::cout << "Looking for: ";
	final.display(std::cout);

	std::cout << " in the text." << std::endl;

	for (std::set<TextQuery::line_no>::const_iterator iter = s.begin();
			iter != s.end(); ++iter)
		std::cout << "line " << *iter << ": " << t.text_line(*iter) << std::endl;

	return 0;
}
