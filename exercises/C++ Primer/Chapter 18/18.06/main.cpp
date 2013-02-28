// Ex 18.06: doing ex 18.01 with lower level commands

#include <iostream>
#include <string>
#include <memory>

template <typename T> class Vector 
{
	public:

		typedef T* iterator;
		typedef const T* const_iterator;

		Vector(): elements(0), first_free(0), end(0) { }

		void push_back(const T&);
		void reserve(unsigned int N);
		void resize(unsigned int N);

		void print() const { for (const_iterator i = elements; i != first_free; ++i) std::cout << *i << " "; std::cout << std::endl; }

		std::ptrdiff_t size() { return first_free - elements; }
		std::ptrdiff_t capacity() { return end - elements; }

		T& operator[](unsigned index) { return *(elements+index);}
		const T& operator[](unsigned index) const { return *(elements+index);}

	private:

		static std::allocator<T> alloc;

		void reallocate(size_t N = 0);

		T* elements;	// first element
		T* first_free;	// first free element position
		T* end;			// one-past-last allocated element
};

template <typename T> std::allocator<T> Vector<T>::alloc;

template <typename T> void Vector<T>::push_back(const T& t)
{
	// check if we have free space preallocated
	if (first_free == end)
		reallocate();
	
	// 18.01: alloc.construct(first_free, t);
	new (first_free) T(t);

	++first_free;
}

template <typename T> void Vector<T>::reallocate(size_t N)
{
	// compute size of current array and allocate space for twice as many elements
	std::ptrdiff_t size = first_free - elements;
	std::ptrdiff_t new_capacity = (!N)? (2 * std::max(size, 1)) : (N);

	// allocate space to hold new_capacity number of elements of type T
	// 18.01: T* new_elements = alloc.allocate(new_capacity);
	T* new_elements = static_cast<T*>(operator new[](new_capacity * sizeof(T)));

	// construct copies of the existing elements in the new space
	std::uninitialized_copy(elements, first_free, new_elements);

	// destroy the old elements in reverse order
	// 18.01: for (T* p = first_free; p != elements; /* empty */)
		// 18.01: alloc.destroy(--p);
	for (T* p = first_free; p != elements; --p)
		p->~T(); // call the destructor

	// deallocate cannot be called on 0 pointer
	if (elements)
		operator delete[](elements);
		// 18.01: alloc.deallocate(elements, end - elements); // return the memory that held the elements

	// make our data structure point to new elements
	elements = new_elements;
	first_free = elements + size;
	end = elements + new_capacity;
}

// reserve(N) makes sure there is at least N places reserved
template <typename T> void Vector<T>::reserve(unsigned int N)
{
	std::ptrdiff_t capacity = end - elements;
	if (capacity < N)
		reallocate(N);
}

template <typename T> void Vector<T>::resize(unsigned int N)
{
	std::ptrdiff_t size = first_free - elements;
	if (size < N)
	{
		for (unsigned int i = (N-size); i != N; ++i)
			push_back(T());
	}
	else if (size >= N)
	{
		// if we have more elements than wanted, we just remove them
		// note that the capacity doesn't change at all
		
		// 18.01: for (T* p = first_free; p != (elements + N); /* empty */)
			// 18.01: alloc.destroy(--p);
		for (T* p = first_free-1; p > (elements + N); --p)
			p->~T(); // call the destructor

		// set first_free correctly to one past of what is left
		first_free = elements + N;
	}
}

int main()
{
	Vector<int> iVec;

	for (int i=20; i != 0; --i)
		iVec.push_back(i);

	std::cout << iVec.size() << "/" << iVec.capacity() << std::endl;
	iVec.print();

	iVec.resize(10);
	std::cout << iVec.size() << "/" << iVec.capacity() << std::endl;
	iVec.print();

	iVec.reserve(100);
	std::cout << iVec.size() << "/" << iVec.capacity() << std::endl;

	const int a = iVec[5];
	std::cout << a << std::endl;

	iVec[5] = -3;
	std::cout << iVec[5] << std::endl;

	Vector<int>::const_iterator iter = &iVec[4];
	std::cout << *iter << std::endl;

	iVec.print();

	return 0;
}
