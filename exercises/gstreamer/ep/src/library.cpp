/*										
 * library.cpp	
 * (c) Markus Klinga
 * 
 */

#include "library.h"
#include "song.h"
#include "global.h"
#include <boost/filesystem.hpp>


/*
 *  UniqueNumber
 */

UniqueNumber::UniqueNumber()
	: _lastNumber(0)
	, _amountOfNumbers(0)
{
	
}

unsigned int UniqueNumber::GenerateNumber()
{
	unsigned int newNumber;

	// if there is released numbers, we give one of them
	if (_releasedNumbers.size() > 0)
	{
		newNumber = _releasedNumbers.front();
		_releasedNumbers.pop();
	}
	else
	{
		// otherwise we return next number available
		newNumber = ++_lastNumber;
	}

	return newNumber;
}

void UniqueNumber::ReleaseNumber(unsigned int num)
{
	_releasedNumbers.push(num);
}


/*
 *  Songlist
 */

Songlist::Songlist()
{
	
}

unsigned int Songlist::_AddSong(Song s)
{
	unsigned int newID = _ID.GenerateNumber();
	_songs.insert(std::make_pair(newID, s));

	return newID;
}

const Song* Songlist::_GetSong(unsigned int wanted) const
{
	if (_songs.find(wanted) != _songs.end())
		return &_songs.at(wanted);
	else
		return NULL;
}

/*
 *  Library
 */


Library::Library()
{

}

void Library::LoadFolder(std::string s)
{
	namespace fs = boost::filesystem;

	fs::path p(s);

	if (!fs::is_directory(p))
	{
		std::cerr << "p is not a directory! (p = " << p << ")" << std::endl;
		return;
	}
	else
	{
		Global::Log.Add("p is indeed a directory.");
		std::vector<fs::path> files;
		std::copy(fs::directory_iterator(p), fs::directory_iterator(), std::back_inserter(files));

		std::vector<std::string> newFiles;

		for (std::vector<fs::path>::const_iterator iter = files.begin();
				iter != files.end(); ++iter)
		{
			std::string s = (*iter).extension().native();
			std::transform(s.begin(), s.end(), s.begin(), ::tolower);

			// FIXME: this is NOT a good way to do this
			if ((s == ".mp3") || (s == ".ogg") || (s == ".wav"))
				newFiles.push_back((*iter).native());
		}

		if (newFiles.size())
		{
			std::sort(newFiles.begin(), newFiles.end());
			Global::Log.Add("Replaced library with " + std::to_string(newFiles.size()) + " items.");

			for (std::vector<std::string>::iterator iter = newFiles.begin();
					iter != newFiles.end(); ++iter)
				{
					_songs._AddSong(Song(*iter));
				}
		}
	}
}

unsigned int Library::AddSingleSong(std::string filename)
{
	// TODO: check that file really exists
	// TODO: check that song is not in library already

	return _songs._AddSong(Song(filename));
}

