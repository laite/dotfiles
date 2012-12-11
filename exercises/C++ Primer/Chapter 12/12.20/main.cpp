// Ex 12.20: abstractions

#include "../../helpers.h"

class Book
{
	public:
		Book() {}
		Book(string name): _name(name) {}
		Book(string name, string author): _name(name), _author(author) {}
	private:
		string _name;
		string _author;
}

int main()
{
	Book almanakka;
	Book phoneBook("Numbers of the world");
	Book topSeller("Twilight", "Who Cares");

	return 0;
}
