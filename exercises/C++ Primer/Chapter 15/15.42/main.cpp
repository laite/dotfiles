// Ex 15.42: modifying text query program to read whole sentences

#include <iostream>
#include <string>
#include <fstream>

#include "query.h"

const std::string DATAFILE("papintytar.txt");

int main()
{
	TextQuery t;
	std::ifstream f(DATAFILE.c_str());
	t.read_file(f);
	f.close();

	Query q("tuli"), q2("meni"), q3("Hän");
	Query final = (q & q2) | q3;

	std::set<TextQuery::sentence_no> s = final.eval(t);

	std::cout << "Looking for: ";
	final.display(std::cout);

	std::cout << " in the text." << std::endl;

	for (std::set<TextQuery::sentence_no>::const_iterator iter = s.begin();
			iter != s.end(); ++iter)
		std::cout << "sentence " << *iter << ": " << t.text_sentence(*iter) << std::endl;

	return 0;
}
