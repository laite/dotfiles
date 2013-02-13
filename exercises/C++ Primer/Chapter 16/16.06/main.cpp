// Ex 16.06: class templates, simple List class

#include <iostream>
#include <string>
#include <list>

// Simple class template with minimal set of member functions
template <class Type> class MyList 
{
	public:

		Type front() { return _list.front(); }
		Type back() { return _list.back(); }

		void push_front(const Type &typeItem) { _list.push_front(typeItem); }

	private:

		std::list<Type> _list;
};

int main()
{
	MyList<int> lista;

	lista.push_front(15);
	std::cout << lista.front() << std::endl;

	return 0;
}
