// Ex 12.13: extending Screen class

#include "../../helpers.h"
#include "../Screen.h"

int main()
{
	Screen s(7, 3);
	s.FillArea('_');

	s.Move(4,2).SetCharacter('#').Display(cout);

	// GetCharacter without arguments returns whatever is under the cursor
	cout << s.GetCharacter() << s.GetCharacter(3, 1) << s.GetCharacter(4, 2) << endl;

	return 0;
}
