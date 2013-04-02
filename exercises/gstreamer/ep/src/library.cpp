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

unsigned long UniqueNumber::GenerateNumber()
{
	unsigned long newNumber;

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

void UniqueNumber::ReleaseNumber(unsigned long num)
{
	_releasedNumbers.push(num);
}


/*
 *  Songlist
 */

Songlist::Songlist()
{
	
}

unsigned long Songlist::_AddSong(Song s)
{
	unsigned long newID = _ID.GenerateNumber();
	_songs.insert(std::make_pair(newID, s));

	return newID;
}

const Song* Songlist::_GetSong(unsigned long wanted) const
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

unsigned long Library::AddSingleSong(std::string filename)
{
	// TODO: check that song is not in library already

	namespace fs = boost::filesystem;

	fs::path p(filename);

	if (!fs::exists(p))
		throw std::invalid_argument("ERROR: AddSingleSong has filename that doesn't seem to exist!");
	else if (!fs::is_regular_file(p))
		throw std::invalid_argument("ERROR: AddSingleSong has non-regular file!");

	return _songs._AddSong(Song(filename));
}

