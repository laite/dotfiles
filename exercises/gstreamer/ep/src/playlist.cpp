/*										
 * playlist.cpp	
 * (c) Markus Klinga
 * 
 */

#include "playlist.h"

Playlist::Playlist()
	: _index(0)
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
	if (newIndex < songlist.size())
		return (( _index = newIndex ));
	else if (newIndex == songlist.size() && _wrap) // wrap around the list
		return (( _index = 0 ));
	else
		return false;
}
