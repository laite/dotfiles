// Ex 5.25 & 5.26 : misparenthing

#include "../Ch5headers.h"

int main()
{

	// Statement:   !ptr == ptr->next
	// Order 	:   ((!ptr) == (ptr->next))
	// Intended (presume):
	if (!(ptr == ptr->next)
	
	// Statement:   ch = buf[ bp++] != '\n'
	// Order 	:   ch = (buf [ (bp++) ] != '\n')

	return 0;
}
