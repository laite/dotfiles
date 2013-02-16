/*										
 * queue.ipp	
 * (c) Markus Klinga
 * 
 * File where templates are implemented
 */

template <class Type> void Queue<Type>::destroy()
{
	while (!empty())
		pop();
}

template <class Type> void Queue<Type>::pop()
{
	// pop is unchecked: Popping off an empty Queue is undefined
	QueueItem<Type>* p = head;
	head = head->next;
	delete p;
}

template <class Type> void Queue<Type>::push(const Type &val)
{
	// allocate a new QueueItem object
	QueueItem<Type> *pt = new QueueItem<Type>(val);

	// put it into an existing Queue
	if (empty())
		head = tail = pt;	// the queue now has only one element
	else
	{
		tail->next = pt; 	// add new element to end of the queue
		tail = pt;
	}
}

template <class Type> void Queue<Type>::copy_elems(const Queue &orig)
{
	// copy elements from orig into this Queue
	// loop stops when pt == 0, which happens when we reach orig.tail
	for (QueueItem<Type> *pt = orig.head; pt; pt = pt->next)
		push(pt->item); // copy the element
}

template <class Type> Queue<Type>& Queue<Type>::operator=(const Queue<Type> &rhs)
{
	destroy();
	copy_elems(rhs);
}

template <class Type> template <class Iterator>
void Queue<Type>::assign(Iterator beg, Iterator end)
{
	destroy();
	copy_elems(beg, end);
}

template <class Type> template <class Iterator>
void Queue<Type>::copy_elems(Iterator beg, Iterator end)
{
	while (beg != end)
		push(*(beg++));
}

template <class Type> std::ostream& operator<<(std::ostream &os, const Queue<Type> &q)
{
	os << "< ";
	QueueItem<Type> *p;

	for (p = q.head; p; p = p->next)
		os << p->item << " ";

	os << ">";
}

template <class Type> std::istream& operator>>(std::istream &is, Queue<Type> &q)
{
	Type item;

	while (is >> item)
		q.push(item);
}


