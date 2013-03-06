/*										
 * playlist.h	
 * (c) Markus Klinga
 * 
 */

#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <vector>
#include "library.h"
#include "song.h"

class Playlist 
{
	public:

		typedef std::vector<Song*>::size_type playlist_index;
		Playlist();

		void FirstSong();
		void NextSong();

		const Song *GetCurrentSong() const { return GetSong(_index); }
		const Song *GetSong(playlist_index index) const;

		const std::string GetCurrentSongPath() const;
		playlist_index GetLibrarySize() const { return songlist.size(); }

		void AddSong(Song *s) { songlist.push_back(s); }

	private:

		std::vector<Song*> songlist;

		playlist_index _index;
		bool _wrap;
		
};


#endif /* end PLAYLIST_H */
