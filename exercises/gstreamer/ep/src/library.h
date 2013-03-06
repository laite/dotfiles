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

#include "song.h"

class Library 
{
	public:

		Library();

		void LoadFolder(std::string);

		std::vector<Song> *GetSongs() { return &songs;}

	private:

		std::vector<Song> songs;
};

#endif /* end LIBRARY_H */
