#ifndef QUEUE_H
#define QUEUE_H

template <class Type> class Queue;
template <class Type> std::ostream& operator<<(std::ostream &os, const Queue<Type> &q);
template <class Type> std::istream& operator>>(std::istream &is, Queue<Type> &q);

template <class Type> class QueueItem
{
	friend class Queue<Type>;
	friend std::ostream& operator<< <Type> (std::ostream&, const Queue<Type>&);

	// private class, no public section
	private:

		QueueItem(const Type &t): item(t), next(0) { }

		Type item;				// value stored in this element
		QueueItem *next;		// pointer to next element in Queue
};

template <class Type> class Queue
{
	friend std::ostream& operator<< <Type> (std::ostream&, const Queue<Type>&);
	friend std::istream& operator>> <Type> (std::istream &is, Queue<Type> &q);

	public:

		// empty Queue
		Queue(): head(0), tail(0) { }

		// copy control to manage pointers to QueueItems in the Queue
		Queue(const Queue &Q): head(0), tail(0) { copy_elements(Q); }

		// construct a Queue from a pair of iterators on some sequence
		template <class Iterator> Queue(Iterator beg, Iterator end):
			head(0), tail(0) { copy_elems(beg, end); }

		// replace current Queue by contents delimited by a pair of iterators
		template <class Iterator> void assign(Iterator, Iterator);

		Queue& operator=(const Queue&);
		~Queue() { destroy(); }

		// unchecked operation: front on an empty Queue is undefined
		Type& front() { return head->item; }
		const Type& front() const { return head->item; }

		void push(const Type&);
		void pop();
		bool empty() const { return head == 0; }

	private:

		QueueItem<Type> *head;			// pointer to first element in Queue
		QueueItem<Type> *tail;			// pointer to last element in Queue

		// utility functions used by copy constructor, assignment and destructor

		void destroy();					// delete all elements
		void copy_elems(const Queue&); 	// copy elements from parameter

		// version of copy_elems that can be used to copy elements from iterator range
		template<class Iterator> void copy_elems(Iterator, Iterator);
};

// template definitions
#include "queue.ipp"

#endif /* end QUEUE_H */
