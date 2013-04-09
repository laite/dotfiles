/*										
 * playlist.cpp	
 * (c) Markus Klinga
 * 
 */

// TODO: take care of deleting unused playlists (might become a problem between sessions,
// when playlist's IDs change)

#include <stdexcept>

#include "playlist.h"
#include "global.h"
#include "engine.h"
#include "config.h"

Playlist::Playlist(unsigned long ID)
	: _currentSong(0)
	, _nextSong(-1)
	, _ID(ID)
	, _uri("/home/laite/.config/laite/ep/list" + std::to_string(_ID) + ".m3u")
{
	Global::Log.Add("Create playlist: " + std::to_string(_ID));
}

Playlist::~Playlist()
{
	
}

const Song *Playlist::GetSong(Playlist::playlist_index index) const
{
	if (index < _songlist.size())
		return Global::player.GetLibrary()->GetSong(_songlist.at(index));
	else
		return NULL;
}

bool Playlist::SelectSong(playlist_index newIndex, bool force)
{
	// follow the recommendation on nextSong (if there is one)
	if ((_nextSong != -1) && (!force))
	{
		newIndex = _nextSong;
		_nextSong = -1;
	}

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

void Playlist::RecommendNextSong(long newNextSong)
{
	if ((newNextSong != -1) && (newNextSong >= _songlist.size()))
		return; // nextSong is out-of-range

	_nextSong = newNextSong;
}

void Playlist::SaveToFile(const std::string file) const
{
	// TODO: make sure path to file exists, create if necessary
	std::ofstream outFile(file.c_str());

	if (!outFile)
	{
		Global::Log.Add("Error! Couldn't open file " + file + " for writing.", false);
		return;
	}

	typedef std::vector<unsigned long>::const_iterator playlist_iter;
	for (playlist_iter iter = _songlist.begin(); iter != _songlist.end(); ++iter)
		outFile << Global::player.GetLibrary()->GetSong(*iter)->GetUri() << std::endl;

	outFile.close();
}

void Playlist::LoadFromFile(const std::string file)
{
	if (file == "")
		return;

	std::ifstream inFile(file.c_str());
	std::vector<std::string> files;
	std::string line;

	while (std::getline(inFile, line))
		files.push_back(line);

	inFile.close();

	for (std::vector<std::string>::iterator iter = files.begin(); iter != files.end(); ++iter)
	{
		// We add song from file to our Library
		// and put its unique ID to playlist
		unsigned long i;

		try
		{
			// AddSingleSong returns unique song ID
			i = Global::player.GetLibrary()->AddSingleSong(*iter);
		}
		catch (std::invalid_argument e)
		{
			Global::Log.Add(e.what(), false);
			continue; // jump to next item, this one was bad
		}

		_songlist.push_back(i);
	}
}

void Playlist::AddQuery(std::string query)
{
	// TODO: Proper query from library
}

