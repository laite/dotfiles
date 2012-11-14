// Ex 12.13: extending Screen class

#include "../../helpers.h"
#include "../Screen.h"

int main()
{
	Screen s(7, 3);
	s.RandomizeContent();

	s.Move(4,2).SetCharacter('#').Display(cout);

	return 0;
}
