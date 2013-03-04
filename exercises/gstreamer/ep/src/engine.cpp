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

void Engine::AddFolderToLibrary(std::string s)
{
	// TODO: add instead of replace
	library.LoadFolder(s);

	// generate song list from whole library for now
	std::vector<Song> *wholeLibrary = library.GetSongs();

	for (std::vector<Song>::iterator songiter = wholeLibrary->begin();
			songiter != wholeLibrary->end(); ++songiter)
		_playlists.at(0)->AddSong(&(*songiter));

}

