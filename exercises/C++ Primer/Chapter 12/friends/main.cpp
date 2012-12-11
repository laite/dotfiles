// friends?

#include "../../helpers.h"

void f()
{
	return;
}

class X;

class Y 
{ 
	public:
		void PrintX(X);
};

class X
{
	friend class Y;
	friend void f();
	public:
		X(int starter = 50): xx(starter) {}
	private:
		int xx;
};

class Z
{
	Y *y;
	void g() { return ::f(); }
};

void Y::PrintX(X x)
{
	// we can access private member of X, since Y is a friend ^o^
	cout << x.xx << endl;
}

int main()
{
	Y testClass;
	testClass.PrintX(200);

	return 0;
}
