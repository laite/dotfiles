#ifndef Screen_h
#define Screen_h

/* we define whole Screen class here in spite of good programming behaviour */

#include "../helpers.h"

const int kDefaultScreenWidth = 80;
const int kDefaultScreenHeight = 24;

// note that cursor knows nothing about screen boundaries
struct Cursor
{
	int x, y;
	Cursor(int a, int b): x(a), y(b) {}
	pair<int, int> GetPosition() const {
		return make_pair(x, y);
	}

	void SetPosition(int newX, int newY) {
		this->x = newX;
		this->y = newY;
	}
};

class Screen
{
	public:
		// get character under cursor or from arbitrary position
		char GetCharacter() const;
		char GetCharacter(int x, int y) const;

		// dimension getters
		int GetWidth() const { return _width; }
		int GetHeight() const { return _height; }

		// move cursor to given position
		Screen& Move(int x, int y);

		// set character at current position
		Screen& SetCharacter(char);

		// dump contents to given output
		Screen& Display(std::ostream &outputStream) { _DumpDisplay(outputStream); return *this; }
		const Screen& Display(std::ostream &outputStream) const { _DumpDisplay(outputStream); return *this; }

		// put random letters (a-z) to area
		void RandomizeContent();
		// fill area with specific char
		void FillArea(char);

		// constructors
		Screen(): _cursor(0,0), _width(kDefaultScreenWidth), _height(kDefaultScreenHeight), _area(vector<char>(kDefaultScreenWidth*kDefaultScreenHeight, '.')) {}
		Screen(int width, int height): _cursor(0,0), _width(width), _height(height), _area(vector<char>(width*height, '.')) {}

	private:
		// actually dump display
		void _DumpDisplay(std::ostream &outputStream) const;

		Cursor _cursor;
		int _width, _height;
		vector<char> _area;
};

char Screen::GetCharacter() const
{
	 pair<int, int> pos = this->_cursor.GetPosition();

	 return Screen::GetCharacter(pos.first, pos.second);
}

char Screen::GetCharacter(int x, int y) const
{
	if (this->_area.size() < (y*this->GetWidth()+x))
		return 0;

	return this->_area.at(y*this->GetWidth()+x);
}

Screen& Screen::Move(int x, int y)
{
	this->_cursor.SetPosition(x, y);

	return *this; 
}

Screen& Screen::SetCharacter(char newChar)
{
	pair<int, int> position = this->_cursor.GetPosition();
	this->_area.at(position.second*this->GetWidth()+position.first) = newChar;

	return *this;
}

void Screen::_DumpDisplay(std::ostream &outputStream) const
{
	vector<char>::const_iterator character = this->_area.begin();
	vector<char>::size_type position = 0;

	while (character != this->_area.end())
	{
		outputStream << *character++;
		if (++position%this->GetWidth() == 0)
			outputStream << "\n";
	}
}

void Screen::FillArea(char c)
{
	vector<char>::iterator it = this->_area.begin();
	while (it != this->_area.end())
		*it++ = c; }

void Screen::RandomizeContent()
{
	vector<char>::iterator it = _area.begin();
	srand(time(NULL));

	while (it != _area.end())
		*it++ = 'a'+rand()%(('z'+1)-'a');
}

#endif
