/*										
 * library.cpp	
 * (c) Markus Klinga
 * 
 */

#include "library.h"
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

Library::Library()
	: _index(0)
{

}

void Library::LoadFolder(std::string s)
{
	fs::path p(s);

	if (!fs::is_directory(p))
	{
		std::cerr << "p is not a directory! (p = " << p << ")" << std::endl;
		return;
	}
	else
	{
		std::cout << "p is indeed a directory." << std::endl;
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
			std::cout << "Replaced filelist with " << newFiles.size() << " items." << std::endl;
			_filelist = newFiles;
			FirstSong(); // reset _index
		}
	}
}

void Library::FirstSong()
{
	_index = 0;
}

void Library::NextSong()
{
	if (_index < (_filelist.size()-1))
		++_index;
	else if (_wrap)
		_index = 0;
	else
		std::cout << "End of playlist" << std::endl;
}

const std::string Library::GetCurrentSongPath() const
{
	std::string result("");

	if (_filelist.size() > _index)
		result = _filelist.at(_index);

	return result;
}

const std::string Library::GetTitle() const
{
	std::string result("");

	if (_filelist.size() > _index)
	{
		TagLib::FileRef file(_filelist.at(_index).c_str());
		if (!file.isNull() && file.tag())
		{
			TagLib::Tag *tag = file.tag();
			result = tag->title().to8Bit();
		}
	}

	return result;
}

const std::string Library::GetArtist() const
{
	std::string result("");

	if (_filelist.size() > _index)
	{
		TagLib::FileRef file(_filelist.at(_index).c_str());
		if (!file.isNull() && file.tag())
		{
			TagLib::Tag *tag = file.tag();
			result = tag->artist().to8Bit();
		}
	}

	return result;
}
