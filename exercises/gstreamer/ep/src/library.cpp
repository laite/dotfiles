/*										
 * library.cpp	
 * (c) Markus Klinga
 * 
 */

#include "library.h"
#include "song.h"
#include "global.h"
#include <boost/filesystem.hpp>

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
					songs.push_back(Song(*iter));
				}
		}
	}
}
