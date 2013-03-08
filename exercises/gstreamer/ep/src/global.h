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
#include <vector>

class Engine;

struct AppOptions
{
	// repeat mode
	enum { REPEAT_NONE, REPEAT_ONE, REPEAT_ALL };
	int repeatMode;

};

class Options 
{
	public:

		Options();
		~Options();

		void LoadOptions(std::string file = "");
		void SaveOptions();

		const AppOptions& GetAppOptions() const { return _appOptions; }
		AppOptions& SetAppOptions() { return _appOptions; }

		std::string GetSettingsFolder();
		
	private:

		AppOptions _appOptions;

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
}

#endif /* end GLOBAL_H */
