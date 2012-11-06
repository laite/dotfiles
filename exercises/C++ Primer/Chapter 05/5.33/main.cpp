// Ex 5.33: rewrite using cast notation

#include "../Ch5headers.h"

int main()
{
	int ival;
	double dval;
	const string *ps;
	char *pc;
	void *pv;

	int iv = 2.33;
	cout << iv;

	// ORIGINAL: pv = (void*)ps
	pv = const_cast<string*>(ps);
	pv = (void *)ps;

	// ORIGINAL: ival = int(*pc)
	ival = static_cast<int>(*pc);

	// ORIGINAL: pv = &dval
	pv = static_cast<void*>(&dval);
	
	// ORIGINAL: pc = (char*)pv;
	pc = static_cast<char*>(pv);

	return 0;
}
