// Ex 13.03: copy constructors

#include "../../helpers.h"

class Point {
	public:
		// Point() is a constructor
		Point ();
		// Point(const Point&) is a copy constructor
		Point (const Point&);
	private:
		static int counter;
};

// default constructor
Point::Point()
{
	cout << ++counter << ". Constructor" << endl;
}

// copy constructor
Point::Point(const Point &arg)
{
	cout << ++counter << ". Copy Constructor" << endl;
}

int Point::counter(0);
// 1. global is created through default constructor
Point global;


Point foo_function(Point arg)
{
	// 3. Point arg is created by copy constructor
	// 4. and so is "local"
	Point local = arg;
	// 5. new Point creates a new Point object by copying global
	// 6. the result is kept alive by pointer called heap
	Point *heap = new Point(global);
	// 7. assign new value to *heap through copy constructor
	*heap = local;
	// 8. and 9. Two items in pa are created through default constructor
	Point pa[ 4 ] = { local, *heap };
	// 10. we return a copy of *heap, obviously made through copy constructor
	return *heap;
}

int main()
{
	// 2. myPoint is created through constructor
	Point myPoint;
	foo_function(myPoint);

	return 0;
}
