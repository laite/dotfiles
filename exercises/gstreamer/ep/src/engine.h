/*										
 * engine.h	
 * (c) Markus Klinga
 * 
 */

#ifndef ENGINE_H
#define ENGINE_H

#include <string>
#include "playback.h"
#include "library.h"

class Engine 
{
	typedef std::vector<Playlist*>::size_type playlist_index;
	public:

		Engine();

		Playback *GetPlayback() { return &playback; }
		Library  *GetLibrary() { return &library; }

		Playlist *GetCurrentPlaylist() { return _playlists[_currentPlaylist]; }

		// there is no boundary checking here
		Playlist *GetPlaylist(playlist_index index) { return _playlists[index]; }

	private:

		// the main library of player
		Library library;

		// the main playback interface
		Playback playback;

		// all playlists
		std::vector<Playlist*> _playlists;

		// index of currently active playlist
		playlist_index _currentPlaylist;
		
};

#endif /* end ENGINE_H */
