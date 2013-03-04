/*										
 * playlist.h	
 * (c) Markus Klinga
 * 
 */

#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <vector>
#include "library.h"

class Playlist 
{
	public:

		Playlist();

		void FirstSong();
		void NextSong();

		const std::string GetTitle() const;
		const std::string GetArtist() const;

		const std::string GetCurrentSongPath() const;
		std::vector<std::string>::size_type GetLibrarySize() const { return songlist.size(); }

		void AddSong(Song *s) { songlist.push_back(s); }

	private:

		std::vector<Song*> songlist;

		std::vector<Song*>::size_type _index;
		bool _wrap;
		
};


#endif /* end PLAYLIST_H */
