/*										
 * query.cpp	
 * (c) Markus Klinga
 * 
 */

#include "query.h"
#include <algorithm>
#include <iterator>

/*
 *  Query
 */

Query::Query(const std::string &s)
	: q(new WordQuery(s))
	, use(new std::size_t(1)) 
{

}

Query::Query(const Query &c)
	: q(c.q)
	, use(c.use)
{
	++*use;
}

Query::Query(Query_base *query)
	: q(query)
	, use(new std::size_t(1)) 
{ 
	// empty body
}

Query::~Query()
{
	decr_use();
}

void
Query::decr_use()
{
	if (--*use == 0)
	{
		delete q;
		delete use;
	}
}


std::set<TextQuery::sentence_no>
Query::eval(const TextQuery &t) const
{
	return q->eval(t);
}

std::ostream&
Query::display(std::ostream &os) const
{
	return q->display(os);
}

/*
 *  WordQuery
 */

std::set<WordQuery::sentence_no>
WordQuery::eval(const TextQuery &t) const
{
	return t.run_query(query_word);
}

std::ostream&
WordQuery::display(std::ostream &os) const
{
	return os << query_word;
}

/*
 *  NotQuery
 */

std::set<NotQuery::sentence_no>
NotQuery::eval(const TextQuery &file) const
{
	// virtual call through the Query handle to eval
	std::set<sentence_no> has_val = query.eval(file);
	std::set<sentence_no> ret_sentences;

	// for each sentence in the input file, check whether that sentence is in has_val
	for (TextQuery::sentence_no n = 0; n != file.size(); ++n)
	{
		// if sentence is not found, we add it to ret_sentences
		if (has_val.find(n) == has_val.end())
			ret_sentences.insert(n);
	}

	return ret_sentences;
}

std::ostream&
NotQuery::display(std::ostream &os) const
{
	return os << "~(" << query << ")";
}

/*
 *  BinaryQuery
 */

std::ostream&
BinaryQuery::display(std::ostream &os) const
{
	return os << "(" << lhs << " " << oper << " " << rhs << ")";
}

/*
 *  OrQuery
 */

std::set<OrQuery::sentence_no>
OrQuery::eval(const TextQuery &file) const
{
	// virtual calls through the Query handle to get result sets for the operands
	std::set<sentence_no> right = rhs.eval(file);
	std::set<sentence_no> ret_sentences = lhs.eval(file); // destination to hold the results

	ret_sentences.insert(right.begin(), right.end());

	return ret_sentences;
}

/*
 *  AndQuery
 */

std::set<AndQuery::sentence_no>
AndQuery::eval(const TextQuery &file) const
{
	std::set<sentence_no> left = lhs.eval(file);
	std::set<sentence_no> right = rhs.eval(file);

	std::set<sentence_no> ret_sentences; // destination to hold the results

	// writes intersection of two ranges to a destination iterator
	// destination iterator in this call adds elements to ret_sentences
	std::set_intersection(left.begin(), left.end(), right.begin(), right.end(),
				inserter(ret_sentences, ret_sentences.begin()));

	return ret_sentences;
}


