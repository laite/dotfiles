// Ex 10.25: books
// requires -std=c++0x to compile

#include "../../helpers.h"

const short kMajorVersion = 0;
const short kMinorVersion = 1;

void print_menu()
{
	cout << "What would you like to do? Type 'help' for available commands." << endl;
}

void print_help()
{
	cout << "Available commands:" << endl;
	cout << "read - read a book" << endl;
	cout << "list [read/suggestions] - list books you've read / not yet read" << endl;
	cout << "remove - remove book from read list" << endl;
	cout << "quit - exit kirjaLaite" << endl;
}

string fetch_book(set<string> &titles, set<string> &readBooks)
{
	set<string>::iterator iter = titles.begin();
	string newBook("");

	while (iter != titles.end() && newBook == "")
	{
		if (readBooks.find(*iter) == readBooks.end())
		{
			newBook = *iter;
			readBooks.insert(*iter);
		}
		++iter;
	}

	if (newBook == "")
		newBook = "nothing anymore. Go out and play.";

	return newBook;
}

void list_read(set<string> &readTitles, string headText)
{
	if (readTitles.empty())
	{
		cout << "No books in list!" << endl;
		return;
	}

	set<string>::iterator iter = readTitles.begin();
	cout << headText << endl;

	while (iter != readTitles.end())
		cout << *iter++ << endl;

	return;
}

bool remove_title_from_read(set<string> &titles)
{
	if (titles.empty())
	{
		cout << "No books in list!" << endl;
		return false;
	}

	list_read(titles, "What title would you like to remove?");

	string answer;
	cin >> answer;

	if (!cin.good())
		return false;

	set<string>::iterator iter = titles.find(answer);

	if (iter != titles.end())
		titles.erase(iter);
	else
		return false;

	cout << "Erased book: " << answer << endl;

	return true;
}

int main()
{
	cout << "Welcome to kirjaLaite!" << endl;
	bool quit = false;

	set<string> titles { "Moskova", "Petuski" };
	set<string> readTitles { "Karamazov", "Ruskolnikov" };

	while (!quit)
	{
		string selection;
		cout << "* KirjaLaite v" << kMajorVersion << "." << kMinorVersion << " *" << endl;
		getline(cin, selection);

		if (selection == "read")
			cout << "You really should read " << fetch_book(titles, readTitles) << endl;
		else if (selection == "list suggestions")
			list_read(titles, "Suggestions left in list: ");
		else if (selection == "list read")
			list_read(readTitles, "You have read these books: ");
		else if (selection == "remove")
			remove_title_from_read(readTitles);
		else if (selection == "quit" || !cin.good())
			quit = true;
		else 
			print_help();
	}

	return 0;
}
