/*										
 * library.cpp	
 * (c) Markus Klinga
 * 
 */

#include "library.h"
#include "song.h"
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
			std::cout << "Replaced library with " << newFiles.size() << " items." << std::endl;

			for (std::vector<std::string>::iterator iter = newFiles.begin();
					iter != newFiles.end(); ++iter)
				{
					songs.push_back(Song(*iter));
				}
		}
	}
}
