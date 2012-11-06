// Ex 9.27: looking for strings

#include "../../helpers.h"

int main()
{
	string wantedWord("penis");
	list<string> source;
	deque<string> sourceDeque;

	string text[] = {"My", "lord!", "I'm", "sad", "to", "announce", "but", "my", "penis", "has", "merged", "into", "your", "penis", " ...call", "me", "maybe" };

	source.insert(source.begin(), text, text + 17);
	sourceDeque.insert(sourceDeque.begin(), source.begin(), source.end());

	list<string>::iterator iter = source.begin();
	deque<string>::iterator dequeIter = sourceDeque.begin();

	while (iter != source.end())
	{
		if (*iter++ == wantedWord)
			iter = source.erase(--iter);
	}

	while (dequeIter != sourceDeque.end())
	{
		if (*dequeIter++ == wantedWord)
			dequeIter = sourceDeque.erase(--dequeIter);
	}

	source.clear();
	// we don't (yet) have PrintDeque - helper, so we assign items to list for printing
	source.assign(sourceDeque.begin(), sourceDeque.end());
	PrintList(source);

	return 0;
}
