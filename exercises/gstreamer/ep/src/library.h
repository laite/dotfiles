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
		unsigned long GenerateNumber();
		void ReleaseNumber(unsigned long);

	private:

		unsigned long _lastNumber;
		std::queue<unsigned long> _releasedNumbers;
		unsigned long _amountOfNumbers;
};

class Songlist 
{
	friend class Library;

	private:

		Songlist();

		// TODO: remember to release unique id when adding removeSong
		unsigned long _AddSong(Song);
		const Song* _GetSong(unsigned long) const;

		UniqueNumber _ID;
		std::map< unsigned long, Song> _songs;
};

class Library 
{
	public:

		Library();

		void LoadFolder(std::string);

		// AddSingleSong returns added song's ID
		// throws std::invalid_argument if file can't be found
		unsigned long AddSingleSong(std::string);

		const Song* GetSong(unsigned long ID) { return _songs._GetSong(ID); }

	private:

		Songlist _songs;
};

#endif /* end LIBRARY_H */
