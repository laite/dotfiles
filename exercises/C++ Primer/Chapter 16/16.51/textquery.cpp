
#include "textquery.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

void TextQuery::store_file(std::ifstream &is)
{
	std::string s;
	while (std::getline(is, s))
		TextQuery::lines_of_text.push_back(s);
}

// map each word in lines_of_text to word_map
void TextQuery::build_map()
{
	TextQuery::line_no lineNumber = 0;

	for (lineNumber = 0; lineNumber != TextQuery::lines_of_text.size(); ++lineNumber)
	{
		std::istringstream ss(TextQuery::lines_of_text[lineNumber]);
		std::string word;
		while (ss >> word)
			TextQuery::word_map[word].insert(lineNumber);
	}
}

std::set<TextQuery::line_no> TextQuery::run_query(const std::string &query) const
{
	std::map<std::string, std::set<TextQuery::line_no> >::const_iterator foundIter = TextQuery::word_map.find(query);
	
	// return empty set<> if there's no match
	if (foundIter == TextQuery::word_map.end())
		return std::set<TextQuery::line_no>();
	else
		return foundIter->second;
}

std::string TextQuery::text_line(TextQuery::line_no lineNumber) const
{
	if (lineNumber < TextQuery::lines_of_text.size())
		return TextQuery::lines_of_text.at(lineNumber);

	throw std::out_of_range("line number out of range!");
}

TextQuery::line_no TextQuery::size() const
{
	return lines_of_text.size();
}

