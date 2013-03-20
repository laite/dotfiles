/*										
 * playlist.h	
 * (c) Markus Klinga
 * 
 */

#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include "song.h"

class Playlist 
{
	public:

		typedef std::vector<Song*>::size_type playlist_index;
		Playlist();

		void LoadFromFile(std::string&);
		void SaveToFile(std::string&) const;

		bool SelectSong(playlist_index);

		void FirstSong() { SelectSong(0); }

		bool PreviousSong() { return SelectSong(_currentSong - 1); }
		bool NextSong() { return SelectSong(_currentSong + 1); }

		const Song *GetCurrentSong() const { return GetSong(_currentSong); }

		// returns NULL if index is out of bounds
		const Song *GetSong(playlist_index index) const;

		playlist_index GetSize() const { return _songlist.size(); }

		void AddSong(Song *s) { _songlist.push_back(s); }
		void AddQuery(std::string);

	private:

		std::vector<Song*> _songlist;

		playlist_index _currentSong;
};


#endif /* end PLAYLIST_H */
