
#include "../helpers.h"
#include "textquery.h"

void TextQuery::store_file(std::ifstream &is)
{
	string s;
	while (getline(is, s))
		TextQuery::lines_of_text.push_back(s);
}

// map each word in lines_of_text to word_map
void TextQuery::build_map()
{
	TextQuery::line_no lineNumber = 0;

	for (lineNumber = 0; lineNumber != TextQuery::lines_of_text.size(); ++lineNumber)
	{
		istringstream ss(TextQuery::lines_of_text[lineNumber]);
		string word;
		while (ss >> word)
			TextQuery::word_map[word].insert(lineNumber);
	}
}

set<TextQuery::line_no> TextQuery::run_query(const string &query) const
{
	map<string, set<TextQuery::line_no> >::const_iterator foundIter = TextQuery::word_map.find(query);
	
	// return empty set<> if there's no match
	if (foundIter == TextQuery::word_map.end())
		return set<TextQuery::line_no>();
	else
		return foundIter->second;
}

string TextQuery::text_line(TextQuery::line_no lineNumber) const
{
	if (lineNumber < TextQuery::lines_of_text.size())
		return TextQuery::lines_of_text.at(lineNumber);

	throw std::out_of_range("line number out of range!");
}
