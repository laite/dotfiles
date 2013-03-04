/*										
 * library.h	
 * (c) Markus Klinga
 * 
 */

#ifndef LIBRARY_H
#define LIBRARY_H

#include <string>
#include <vector>

class Library 
{
	public:

		Library();

		void LoadFolder(std::string);

		void FirstSong();
		void NextSong();
		std::string GetCurrentSong() const;
		std::vector<std::string>::size_type GetLibrarySize() const { return _filelist.size(); }

	private:

		std::vector<std::string>::size_type _index;
		std::vector<std::string> _filelist;
		
		bool _wrap; // do we repeat from beginning
};

#endif /* end LIBRARY_H */
