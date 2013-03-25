/*										
 * library.h	
 * (c) Markus Klinga
 * 
 */

#ifndef LIBRARY_H
#define LIBRARY_H

#include <string>
#include <vector>
#include <fileref.h>
#include <tag.h>
#include <map>
#include <queue>

#include "song.h"

class UniqueNumber
{
	public:
		UniqueNumber();
		unsigned int GenerateNumber();
		void ReleaseNumber(unsigned int);

	private:

		unsigned int _lastNumber;
		std::queue<unsigned int> _releasedNumbers;
		unsigned int _amountOfNumbers;
};

class Songlist 
{
	friend class Library;

	private:

		Songlist();

		// TODO: remember to release unique id when adding removeSong
		unsigned int _AddSong(Song);
		const Song* _GetSong(unsigned int) const;

		UniqueNumber _ID;
		std::map< unsigned int, Song> _songs;
};

class Library 
{
	public:

		Library();

		void LoadFolder(std::string);

		// AddSingleSong returns added song's ID
		unsigned int AddSingleSong(std::string);

		const Song* GetSong(unsigned int ID) { return _songs._GetSong(ID); }

	private:

		Songlist _songs;
};

#endif /* end LIBRARY_H */
