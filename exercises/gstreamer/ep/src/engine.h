/*										
 * engine.h	
 * (c) Markus Klinga
 * 
 */

#ifndef ENGINE_H
#define ENGINE_H

#include <string>
#include <boost/signal.hpp>

#include "playback.h"
#include "library.h"
#include "global.h"

class Engine 
{
	typedef std::vector<Playlist*>::size_type playlist_index;
	typedef boost::signal<void ()>::slot_function_type cb_type;

	public:

		Engine();

		Playback *GetPlayback() { return &playback; }
		Library  *GetLibrary() { return &library; }

		Playlist *GetCurrentPlaylist() { return _playlists[_currentPlaylist]; }

		// there is no boundary checking here
		Playlist *GetPlaylist(playlist_index index) { return _playlists[index]; }

		int HookToEvent(Global::EVENT, cb_type cb);
		bool UnhookFromEvent(Global::EVENT, int);

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
