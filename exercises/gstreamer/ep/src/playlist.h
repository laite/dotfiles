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

		Playlist(unsigned int);
		~Playlist();

		// File operations
		void LoadFromFile(const std::string);
		void SaveToFile(const std::string) const;

		// Change active song on playlist
		// TODO: trigger
		bool SelectSong(playlist_index);

		// Some helpers for SelectSong
		void FirstSong() { SelectSong(0); }
		bool PreviousSong() { return SelectSong(_currentSong - 1); }
		bool NextSong() { return SelectSong(_currentSong + 1); }

		// return pointer to currently active song
		const Song* GetCurrentSong() const { return GetSong(_currentSong); }

		// returns NULL if index is out of bounds
		const Song* GetSong(playlist_index index) const;

		// return vector (song ID) reference
		const std::vector<unsigned int>& GetAllSongIDs() const { return _songlist; }

		const playlist_index GetSize() const { return _songlist.size(); }
		const Glib::ustring GetName() const { return _name; }
		const Glib::ustring GetUri() const { return _uri; }

		// add single song to the end of playlist
		void AddSong(unsigned int song) { _songlist.push_back(song); }

		// Query songs from library and add matching to playlist
		void AddQuery(std::string);

	private:

		// list of all songs playlist holds
		// (unique song ID's)
		std::vector<unsigned int> _songlist;

		// index of currently active song [0..n[
		playlist_index _currentSong;

		// name of playlist (shows to user)
		Glib::ustring _name;

		// unique playlist id
		unsigned int _ID;

		// filepath of playlist
		Glib::ustring _uri;
};


#endif /* end PLAYLIST_H */
