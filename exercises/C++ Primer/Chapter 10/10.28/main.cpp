// Ex 10.28: multimaps and authors, pt. III

#include "../../helpers.h"

typedef multimap<string, string>::iterator authorIterator;

void PrintBooksByAuthor(multimap<string, string> &books, string author)
{
	pair<authorIterator, authorIterator> iterPair = books.equal_range(author);

	if (iterPair.first != iterPair.second)
		cout << "Books by " << author << ": " << flush;
	else
		cout << "No books by " << author << "." << endl;

	while (iterPair.first != iterPair.second)
	{
		cout << iterPair.first->second;
		if (++iterPair.first != iterPair.second)
			cout << ", ";
		else
			cout << endl;
	}	


	return;
}

void EraseAuthor(multimap<string, string> &books, string author)
{
	pair<authorIterator, authorIterator> authorRange = books.equal_range(author);

	cout << "!! Erasing all books by " << author << " !!" << endl;

	while (authorRange.first != authorRange.second)
		books.erase(authorRange.first++);
	
	return;
}

void PrintAllBooks(multimap<string, string> &books)
{
	authorIterator book = books.begin();
	char firstCharacter = ' ';
	string author(""), lastAuthor("");

	while (book != books.end())
	{
		author = book->first;
		if (author.at(0) != firstCharacter)
		{
			firstCharacter = author.at(0);
			cout << "## Author names beginning with '" << firstCharacter << "':" << endl;
		}
		if (author != lastAuthor)
			PrintBooksByAuthor(books, author);

		lastAuthor = author;
		++book;
	}

	return;
}

int main()
{
	multimap<string, string> books;

	books.insert(make_pair("Dostojevski", "Brothers Karamazov"));
	books.insert(make_pair("Dostojevski", "Crime And Punishment"));
	books.insert(make_pair("Dostojevski", "Idiot"));
	books.insert(make_pair("Solzenitsyn", "First Circle"));
	books.insert(make_pair("Solzenitsyn", "The Gulag Islands"));
	books.insert(make_pair("Gogol", "Nose and other short stories"));
	books.insert(make_pair("Gogol", "Dead souls"));
	books.insert(make_pair("Dickens", "Great Expectations"));
	books.insert(make_pair("Dickens", "David Copperfield"));
	books.insert(make_pair("Dickens", "The Christmas Carol"));
	books.insert(make_pair("Anhava", "Vertikalization"));
	books.insert(make_pair("Denholm", "My Life"));
	books.insert(make_pair("Denholm", "My Life")); // There can be two (or more) identical key,value - pairs


	cout << "Printing out all books in database." << endl << endl;

	PrintAllBooks(books);

	return 0;
}
