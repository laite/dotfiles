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
	: h(new WordQuery(s))
{

}

Query::Query(const Query &c)
	: h(c.h)
{
}


Query::Query(Query_base *query)
	: h(query)
{ 
	// empty body
}


Query::~Query()
{
}

std::set<TextQuery::line_no>
Query::eval(const TextQuery &t) const
{
	return h->eval(t);
}

std::ostream&
Query::display(std::ostream &os) const
{
	return h->display(os);
}

/*
 *  WordQuery
 */

std::set<WordQuery::line_no>
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

std::set<NotQuery::line_no>
NotQuery::eval(const TextQuery &file) const
{
	// virtual call through the Query handle to eval
	std::set<line_no> has_val = query.eval(file);
	std::set<line_no> ret_lines;

	// for each line in the input file, check whether that line is in has_val
	for (TextQuery::line_no n = 0; n != file.size(); ++n)
	{
		// if line is not found, we add it to ret_lines
		if (has_val.find(n) == has_val.end())
			ret_lines.insert(n);
	}

	return ret_lines;
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

std::set<OrQuery::line_no>
OrQuery::eval(const TextQuery &file) const
{
	// virtual calls through the Query handle to get result sets for the operands
	std::set<line_no> right = rhs.eval(file);
	std::set<line_no> ret_lines = lhs.eval(file); // destination to hold the results

	ret_lines.insert(right.begin(), right.end());

	return ret_lines;
}

/*
 *  AndQuery
 */

std::set<AndQuery::line_no>
AndQuery::eval(const TextQuery &file) const
{
	std::set<line_no> left = lhs.eval(file);
	std::set<line_no> right = rhs.eval(file);

	std::set<line_no> ret_lines; // destination to hold the results

	// writes intersection of two ranges to a destination iterator
	// destination iterator in this call adds elements to ret_lines
	std::set_intersection(left.begin(), left.end(), right.begin(), right.end(),
				inserter(ret_lines, ret_lines.begin()));

	return ret_lines;
}


