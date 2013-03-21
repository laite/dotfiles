/*										
 * playlist.cpp	
 * (c) Markus Klinga
 * 
 */

#include "playlist.h"
#include "global.h"
#include "engine.h"
#include "config.h"

Playlist::Playlist()
	: _currentSong(0)
{

}

const Song *Playlist::GetSong(Playlist::playlist_index index) const
{
	if (index < _songlist.size())
		return _songlist[index];
	else
		return NULL;
}

bool Playlist::SelectSong(playlist_index newIndex)
{
	int repeat = Global::options.GetAppOptions().repeatMode;

	if (newIndex < _songlist.size())
		_currentSong = newIndex;
	else if ((newIndex == _songlist.size()) && (repeat == AppOptions::REPEAT_ALL)) // wrap around the list
		_currentSong = 0;
	else
		return false;

	Global::player.TriggerEvent(Global::EVENT::E_SONG_CHANGED);
	return true;
}

void Playlist::SaveToFile(std::string &file) const
{
	std::ofstream outFile(file.c_str());

	if (!outFile)
	{
		Global::Log.Add("Error! Couldn't open file " + file + " for writing.", false);
		return;
	}

	typedef std::vector<Song*>::const_iterator playlist_iter;
	for (playlist_iter iter = _songlist.begin(); iter != _songlist.end(); ++iter)
		outFile << (*iter)->GetUri() << std::endl;

	outFile.close();
}

void Playlist::LoadFromFile(std::string &file)
{
	
}

void Playlist::AddQuery(std::string query)
{
	// TODO: Just get everything for now

	std::vector<Song> *wholeLibrary = Global::player.GetLibrary()->GetSongs();

	for (std::vector<Song>::size_type i = 0; i != wholeLibrary->size(); ++i)
		AddSong(&wholeLibrary->at(i));
}

