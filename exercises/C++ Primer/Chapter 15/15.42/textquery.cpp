
#include "textquery.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

void TextQuery::store_file(std::ifstream &is)
{
	std::string word, sentence("");
	unsigned found;

	while (is >> word)
	{
		sentence += word + " ";
		found = word.find_first_of(".?!");

		if (found != std::string::npos)
		{
			TextQuery::sentences_of_text.push_back(sentence);
			sentence = "";
		}
	}
}

// map each word in sentences_of_text to word_map
void TextQuery::build_map()
{
	TextQuery::sentence_no sentenceNumber = 0;

	for (sentenceNumber = 0; sentenceNumber != TextQuery::sentences_of_text.size(); ++sentenceNumber)
	{
		std::istringstream ss(TextQuery::sentences_of_text[sentenceNumber]);
		std::string word;
		while (ss >> word)
			TextQuery::word_map[word].insert(sentenceNumber);
	}
}

std::set<TextQuery::sentence_no> TextQuery::run_query(const std::string &query) const
{
	std::map<std::string, std::set<TextQuery::sentence_no> >::const_iterator foundIter = TextQuery::word_map.find(query);
	
	// return empty set<> if there's no match
	if (foundIter == TextQuery::word_map.end())
		return std::set<TextQuery::sentence_no>();
	else
		return foundIter->second;
}

std::string TextQuery::text_sentence(TextQuery::sentence_no sentenceNumber) const
{
	if (sentenceNumber < TextQuery::sentences_of_text.size())
		return TextQuery::sentences_of_text.at(sentenceNumber);

	throw std::out_of_range("sentence number out of range!");
}

TextQuery::sentence_no TextQuery::size() const
{
	return sentences_of_text.size();
}

