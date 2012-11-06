// Ex 10.27: multimaps, part II

#include "../../helpers.h"

typedef multimap<string, string>::iterator authorIterator;

void PrintBooksByAuthor(multimap<string, string> &books, string author)
{
	pair<authorIterator, authorIterator> iterPair = books.equal_range(author);

	if (iterPair.first != iterPair.second)
		cout << "Books by " << author << ":" << endl;
	else
		cout << "No books by " << author << "." << endl;

	while (iterPair.first != iterPair.second)
	{
		cout << "- " << iterPair.first->second << endl;
		++iterPair.first;
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

	PrintBooksByAuthor(books, "Gogol");
	EraseAuthor(books, "Gogol");
	PrintBooksByAuthor(books, "Gogol");

	return 0;
}
