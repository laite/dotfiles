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

void Playlist::FirstSong()
{
	_index = 0;
}

void Playlist::NextSong()
{
	if (_index < (songlist.size()-1))
		++_index;
	else if (_wrap)
		_index = 0;
	else
		std::cout << "End of playlist" << std::endl;
}

const std::string Playlist::GetCurrentSongPath() const
{
	std::string result("");

	if (songlist.size() > _index)
		result = songlist.at(_index)->GetUri();

	return result;
}

const Song *Playlist::GetSong(Playlist::playlist_index index) const
{
	return songlist.at(index);
}

