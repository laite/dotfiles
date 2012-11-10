// Ex 12.09: Screen+Cursor, toying with

#include "../../helpers.h"

const int kDefaultScreenWidth = 80;
const int kDefaultScreenHeight = 24;

struct Cursor
{
	int x, y;
	Cursor(int a, int b): x(a), y(b) {}
	pair<int, int> getPosition() const {
		return make_pair(x, y);
	}
};

class Screen
{
	public:
		// get character under cursor or from arbitrary position
		char get(Cursor &) const;
		char get(int x, int y) const { return _area[y*_width+x]; }

		// dimension getters
		int GetWidth() { return _width; }
		int GetHeight() { return _height; }

		// put random letters (a-z) to area
		void RandomizeContent();

		// constructors
		Screen(): _width(kDefaultScreenWidth), _height(kDefaultScreenHeight), _area(vector<char>(kDefaultScreenWidth*kDefaultScreenHeight)) {}
		Screen(int width, int height): _width(width), _height(height), _area(vector<char>(width*height)) {}

	private:
		int _width, _height;
		vector<char> _area;
};

char Screen::get(Cursor &cursor) const
{
	 pair<int, int> pos = cursor.getPosition();

	 return Screen::get(pos.first, pos.second);
}

void Screen::RandomizeContent()
{
	vector<char>::iterator it = _area.begin();
	srand(time(NULL));

	while (it != _area.end())
		*it++ = 'a'+rand()%(('z'+1)-'a');
}

int main()
{
	Screen testScreen(100, 10);
	Cursor cursor(65, 2);

	testScreen.RandomizeContent();
	cout << "get(65,2)  : " << testScreen.get(65, 2) << endl;
	cout << "get(cursor): " << testScreen.get(cursor) << endl;

	return 0;
}
