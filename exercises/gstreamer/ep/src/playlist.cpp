/*										
 * playlist.cpp	
 * (c) Markus Klinga
 * 
 */

#include "playlist.h"

Playlist::Playlist()
	: _currentSong(0)
{

}

const Song *Playlist::GetSong(Playlist::playlist_index index) const
{
	if (index < songlist.size())
		return songlist[index];
	else
		return NULL;
}

bool Playlist::SelectSong(playlist_index newIndex)
{
	int repeat = Global::options.GetAppOptions().repeatMode;

	if (newIndex < songlist.size())
		_currentSong = newIndex;
	else if ((newIndex == songlist.size()) && (repeat == AppOptions::REPEAT_ALL)) // wrap around the list
		_currentSong = 0;
	else
		return false;

	return true;
}
