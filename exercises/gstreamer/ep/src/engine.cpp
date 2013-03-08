/*										
 * engine.cpp	
 * (c) Markus Klinga
 * 
 */

#include "engine.h"

Engine::Engine()
	: _currentPlaylist(0)
{
	if (!_playlists.size())
		_playlists.push_back(new Playlist);

	// TODO: save active playlist on exit, restore here
	playback.SetActivePlaylist(_playlists.at(_currentPlaylist));
}

