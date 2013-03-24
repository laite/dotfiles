/*										
 * playlist.cpp	
 * (c) Markus Klinga
 * 
 */

#include <stdexcept>

#include "playlist.h"
#include "global.h"
#include "engine.h"
#include "config.h"

Playlist::Playlist()
	: _currentSong(0)
{

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
	// TODO: make sure path to file exists, create if necessary
	std::ofstream outFile(file.c_str());

	if (!outFile)
	{
		Global::Log.Add("Error! Couldn't open file " + file + " for writing.", false);
		return;
	}

	typedef std::vector<unsigned int>::const_iterator playlist_iter;
	for (playlist_iter iter = _songlist.begin(); iter != _songlist.end(); ++iter)
		outFile << Global::player.GetLibrary()->GetSong(*iter)->GetUri() << std::endl;

	outFile.close();
}

void Playlist::LoadFromFile(std::string &file)
{
	std::ifstream inFile(file.c_str());
	std::vector<std::string> files;
	std::string line;

	while (std::getline(inFile, line))
		files.push_back(line);

	inFile.close();

	for (std::vector<std::string>::iterator iter = files.begin(); iter != files.end(); ++iter)
	{
		// TODO: Load here
		unsigned int i = Global::player.GetLibrary()->AddSingleSong(*iter);
		_songlist.push_back(i);
	}
}

void Playlist::AddQuery(std::string query)
{
	// TODO: Proper query from library
}

