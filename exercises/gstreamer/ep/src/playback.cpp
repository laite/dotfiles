/*										
 * playback.cpp	
 * (c) Markus Klinga
 * 
 */

#include "playback.h"

Playback::Playback(Library *l)
	: library(l)
	, _playing(false)
{
	
}

void Playback::StartPlayback()
{
	Glib::ustring song = library->GetCurrentSong();
	sound.StartPlaying(song);
	_playing = true;
}

void Playback::StopPlayback()
{
	if (_playing)
	{
		sound.StopPlaying();
		_playing = false;
	}

}

void Playback::NextSong()
{
	library->NextSong();
}

