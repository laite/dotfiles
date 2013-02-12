// textquery.h
// Contains TextQuery class declarations

#ifndef TEXTQUERY_H
#define TEXTQUERY_H

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>

class TextQuery {

	public:

		// typedef to make declarations easier
		typedef std::vector<std::string>::size_type sentence_no;

		/* interface:
		 * read_file builds internal data structures for the given file
		 * run_query finds the given word and returns set of sentences on which it appears
		 * text_sentence returns a requested sentence from the input file
		 */

		void read_file(std::ifstream &is) {
			store_file(is);
			build_map();
		}

		std::set<sentence_no> run_query(const std::string&) const;
		std::string text_sentence(sentence_no) const;

		sentence_no size() const;

	private:

		//  utility functions used by read_file
		void store_file(std::ifstream&); // store input file
		void build_map(); // associate each word with a set of sentence numbers

		// remember the whole input file
		std::vector<std::string> sentences_of_text;

		// map word to set of the sentences on which it occurs
		std::map< std::string, std::set<sentence_no> > word_map;
};

#endif
