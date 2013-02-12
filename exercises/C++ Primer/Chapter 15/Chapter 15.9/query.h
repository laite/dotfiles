/*										
 * query.h	
 * (c) Markus Klinga
 * 
 */

#ifndef QUERY_H
#define QUERY_H

#include <set>
#include <iostream>
#include "textquery.h"

class Query_base;

class Query 
{
	// these operators need access to the Query_base* constructor
	friend Query operator~(const Query&);
	friend Query operator|(const Query&, const Query&);
	friend Query operator&(const Query&, const Query&);

	public:

		Query(const std::string&); // builds a new WordQuery		

		// copy control to manage pointers and use counting
		Query(const Query&); 

		~Query();
		Query& operator=(const Query&);

		/*
		 *  Interface functions
		 */
		
		std::set<TextQuery::line_no> eval(const TextQuery&) const;
		std::ostream& display(std::ostream&) const;

	private:

		Query(Query_base *query);

		Query_base *q;
		std::size_t *use;
		void decr_use();
};


class Query_base 
{
	friend class Query;

	protected:

		typedef TextQuery::line_no line_no;
		virtual ~Query_base() { }

	private:

		// eval returns the |set| of lines that this Query matches
		virtual std::set<line_no> eval(const TextQuery&) const = 0;

		// display prints the query
		virtual std::ostream& display(std::ostream& = std::cout) const = 0;
		
};

class WordQuery : public Query_base 
{
	friend class Query;

	private:

		WordQuery(const std::string &s): query_word(s) { }

		// concrete class: WordQuery defines all inherited pure virtual functions
		std::set<line_no> eval(const TextQuery &t) const;
		std::ostream& display(std::ostream &os) const;

		std::string query_word; // word for which to search
		
};

class NotQuery : public Query_base 
{
	friend Query operator~(const Query&);

	private:

		NotQuery(Query q): query(q) { }

		// concrete class
		std::set<line_no> eval(const TextQuery &t) const;
		std::ostream& display(std::ostream &os) const;

		const Query query;
};

class BinaryQuery : public Query_base 
{
	protected:

		BinaryQuery(Query left, Query right, std::string op):
			lhs(left), rhs(right), oper(op) { }		

		// abstract class: BinaryQuery doesn't define eval
		std::ostream& display(std::ostream &os) const;

		const Query lhs, rhs; // left- and right-hand operands
		const std::string oper; // name of the operator
};

class AndQuery : public BinaryQuery 
{
	friend Query operator&(const Query&, const Query&);

	private:
		
		AndQuery(Query left, Query right): BinaryQuery(left, right, "&") { }

		std::set<line_no> eval(const TextQuery&) const;
};

class OrQuery : public BinaryQuery 
{
	friend Query operator|(const Query&, const Query&);

	private:
		
		OrQuery(Query left, Query right): BinaryQuery(left, right, "|") { }

		std::set<line_no> eval(const TextQuery&) const;
};

inline Query operator&(const Query &lhs, const Query &rhs)
{
	return new AndQuery(lhs, rhs);
}

inline Query operator|(const Query &lhs, const Query &rhs)
{
	return new OrQuery(lhs, rhs);
}

inline Query operator~(const Query &oper)
{
	return new NotQuery(oper);
}

inline std::ostream&
operator<<(std::ostream &os, const Query &q)
{
	return q.display(os);
}

#endif /* end QUERY_H */
