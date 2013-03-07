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

		const AppOptions& GetAppOptions() const { return appOptions; }
		AppOptions& SetAppOptions() { return appOptions; }

	private:

		AppOptions appOptions;
		
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
	extern Options options;
	extern LogClass Log;

	extern bool debugMode;
}

#endif /* end GLOBAL_H */
