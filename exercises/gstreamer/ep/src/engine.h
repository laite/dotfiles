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

		void AddFolderToLibrary(std::string s);
		Playback *GetPlayback() { return &playback; }

	private:

		Library library;
		Playback playback;

		std::vector<Playlist*> _playlists;
		std::vector<Playlist*>::size_type _currentPlaylist;
		
};

#endif /* end ENGINE_H */
