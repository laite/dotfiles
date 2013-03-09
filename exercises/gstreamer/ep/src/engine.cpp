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

	// TODO: save active playlist index on exit, restore here
	playback.SetActivePlaylist(_playlists.at(_currentPlaylist));
}

int Engine::HookToEvent(Global::EVENT, Engine::cb_type cb)
{
	// TODO: handle actual hook
}

bool Engine::UnhookFromEvent(Global::EVENT, int)
{
	
}
