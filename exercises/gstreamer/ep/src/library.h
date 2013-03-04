/*										
 * library.h	
 * (c) Markus Klinga
 * 
 */

#ifndef LIBRARY_H
#define LIBRARY_H

#include <string>
#include <vector>
#include <fileref.h>
#include <tag.h>

class Library 
{
	public:

		Library();

		void LoadFolder(std::string);

		void FirstSong();
		void NextSong();

		const std::string GetTitle() const;
		const std::string GetArtist() const;

		const std::string GetCurrentSongPath() const;
		std::vector<std::string>::size_type GetLibrarySize() const { return _filelist.size(); }

	private:

		std::vector<std::string>::size_type _index;
		std::vector<std::string> _filelist;
		
		bool _wrap; // do we repeat from beginning
};

#endif /* end LIBRARY_H */
