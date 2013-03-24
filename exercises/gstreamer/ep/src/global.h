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

	// Do not change starting point (zero) or add anything after E_LAST
	// E_LAST is just a placeholder for last item
	// Cause of each event in comment
	enum EVENT {
		// when currently focused song changes
		E_SONG_CHANGED = 0,

		// triggered each second music is actually playing
		E_PLAYBACK_SECOND,

		// when playback is started/stopped/paused
		E_PLAYBACK_STATUS_CHANGED,

		// placeholder, never triggered
		E_LAST
	};
}

#endif /* end GLOBAL_H */
