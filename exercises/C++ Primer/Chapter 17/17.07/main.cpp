// Ex 17.07: generating exception safe code

#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>

/*
 *  Exercise: a bad function that leaks memory
 */

void bad_function(int *a, int *b)
{
	std::vector<int> v(a, b);
	int *p = new int[v.size()];

	// exception happens here
	// function is terminated without freeing the memory allocated to p
	throw std::runtime_error("whumm!");
}


/*
 *  method 1: catch exception immediately
 */


// fixed_function explicitly tells that it will throw runtime_error (if anything)
void fixed_function1(int *a, int *b) throw(std::runtime_error)
{
	std::vector<int> v(a, b);

	int *p = new int[v.size()];
	
	try
	{
		// exception happens here
		throw std::runtime_error("whumm!");
	}
	catch (std::exception &e)
	{
		// we catch it immediately, so we can handle freeing memory
		// we could also just add another throw; to send exception back in stack
		// instead of handling everything here
		delete [] p;
		std::cout << "exception " << e.what() << " noticed, freeing memory." << std::endl;
	}
}


/*
 *  method 2: use classes to allocate and free resources
 */


template<class T> class Resource 
{
	public:

		explicit Resource(T sizeNeeded): t(new T[sizeNeeded]) { }
		~Resource() { delete [] t; std::cerr << "Freed memory for t in class Resource." << std::endl; }

	private:

		T* t;
		
};
void fixed_function2(int *a, int *b)
{
	std::vector<int> v(a, b);
	Resource<int> p(v.size());

	// exception happens here
	// class destructor is called when it goes out of scope
	throw std::runtime_error("whumm!");
}

int main()
{
	int tableOfInts[] = { 1, 2, 3, 4, 5, 6, 7, 8};
	try
	{
		fixed_function1(tableOfInts, tableOfInts+8);
		fixed_function2(tableOfInts, tableOfInts+8);
	}
	catch (...)
	{
		std::cerr << "Catch!" << std::endl;
	}

	return 0;
}
