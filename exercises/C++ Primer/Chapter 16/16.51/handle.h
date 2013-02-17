#ifndef HANDLE_H
#define HANDLE_H

#include <iostream>
#include <string>
#include <stdexcept>
#include <cassert>

// Generic handle class
template <class T> class Handle
{
	public:

		// unbound handle
		Handle(T *p = 0): ptr(p), use(new std::size_t(1)) { }

		// overloaded operators to support pointer behaviour
		T& operator*();
		T* operator->();
		const T& operator*() const;
		const T* operator->() const;

		// copy control: normal pointer behavior, but last Handle deletes the object
		Handle(const Handle& h): ptr(h.ptr), use(h.use) { ++*use; }

		Handle& operator=(const Handle&);
		~Handle() { rem_ref(); }

	private:

		T* ptr;				// shared object
		std::size_t *use;	// count of how many Handles point to *ptr
		void rem_ref() { if (--*use == 0) { delete ptr; delete use; }}
};

template <class T>
inline Handle<T>& Handle<T>::operator=(const Handle &rhs)
{
	++*rhs.use; // this prevents errors on self-assignments (*use is at least 2)
	rem_ref();
	ptr = rhs.ptr;
	use = rhs.use;

	return *this;
}

template <class T>
inline T& Handle<T>::operator*()
{
	if (ptr)
		return *ptr;
	else
		throw std::runtime_error("dereference of an unbound Handle!");
}

template <class T>
inline const T* Handle<T>::operator->() const
{
	if (ptr)
		return ptr;
	else
		throw std::runtime_error("access through an unbound Handle!");
}

template <class T>
inline const T& Handle<T>::operator*() const
{
	if (ptr)
		return *ptr;
	else
		throw std::runtime_error("dereference of an unbound Handle!");
}

template <class T>
inline T* Handle<T>::operator->()
{
	if (ptr)
		return ptr;
	else
		throw std::runtime_error("access through an unbound Handle!");
}
#endif /* end HANDLE_H */
