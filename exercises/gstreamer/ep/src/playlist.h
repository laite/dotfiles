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
#include "global.h"

class Playlist 
{
	public:

		typedef std::vector<Song*>::size_type playlist_index;
		Playlist();

		bool SelectSong(playlist_index);

		void FirstSong() { SelectSong(0); }
		bool PreviousSong() { return SelectSong(_currentSong - 1); }
		bool NextSong() { return SelectSong(_currentSong + 1); }

		const Song *GetCurrentSong() const { return GetSong(_currentSong); }

		// returns NULL if index is out of bounds
		const Song *GetSong(playlist_index index) const;

		playlist_index GetSize() const { return songlist.size(); }

		void AddSong(Song *s) { songlist.push_back(s); }

	private:

		std::vector<Song*> songlist;

		playlist_index _currentSong;
};


#endif /* end PLAYLIST_H */
