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
	public:

		Engine();

		Playback *GetPlayback() { return &playback; }
		Playlist *GetCurrentPlaylist() { return _playlists[_currentPlaylist]; }
		Library *GetLibrary() { return &library; }

	private:

		// the main library of player
		Library library;

		// the main playback interface
		Playback playback;

		// all playlists
		std::vector<Playlist*> _playlists;

		// index of currently active playlist
		std::vector<Playlist*>::size_type _currentPlaylist;
		
};

#endif /* end ENGINE_H */
