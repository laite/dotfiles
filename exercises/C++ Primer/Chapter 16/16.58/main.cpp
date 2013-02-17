// Chapter 16.58: implementing template override for char*
// Requires C++11 (extended initializer list on vector)

#include <iostream>
#include <string>
#include <vector>

#include "queue.h"

int main()
{
	Queue<char *> iQueue;
	Queue<int> userQ;
	Queue<std::string> userStringQ;
	char word[] = "word!";

	for (int i=0; i != 10; ++i)
		iQueue.push(word);

	std::cout << iQueue << std::endl;

	return 0;
}
