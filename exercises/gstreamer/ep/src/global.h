/*										
 * global.h	
 * (c) Markus Klinga
 * 
 */

#ifndef GLOBAL_H
#define GLOBAL_H

#include <chrono>
#include <iostream>
#include <string>
#include <queue>

class Engine;
class Options;

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

class LogClass 
{
	public:

		void Add(std::string s, bool debugOnly = true);

	private:

		std::vector<std::string> _history;
};

namespace Global
{
	extern Engine player;

	extern Options options;
	extern LogClass Log;

	extern bool debugMode;


	enum EVENT { E_SONG_CHANGED, E_PLAYBACK_SECOND };
}

#endif /* end GLOBAL_H */
