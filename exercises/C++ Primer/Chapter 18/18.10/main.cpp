// Ex 18.10

#include <iostream>
#include <string>
#include <vector>

class iStack 
{
	public:

		iStack(int capacity): stack(capacity), top(0) { }

	private:

		int top;
		std::vector<int> stack;
};

int main()
{
	iStack *ps = new iStack(20);
	// error without preceding const
	const iStack *ps2 = new const iStack(16);

	// error:
	// iStack *ps3 = new iStack[ 100 ];

	return 0;
}
