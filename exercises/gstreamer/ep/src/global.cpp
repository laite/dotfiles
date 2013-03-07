/*										
 * global.cpp	
 * (c) Markus Klinga
 * 
 */

#include "global.h"

Options Global::options;

Options::Options()
{
	// TODO: Load Options
	appOptions.repeatMode = AppOptions::REPEAT_ALL;
}

Options::~Options()
{
	// TODO: Save options here
}

void LogClass::Add(std::string message, bool debugOnly)
{
	if ((debugOnly) && (!Global::debugMode))
		return;

	std::chrono::system_clock::time_point today = std::chrono::system_clock::now();
	std::time_t tt = std::chrono::system_clock::to_time_t ( today );
	std::string timeStamp(ctime(&tt));
	timeStamp = timeStamp.substr(0, timeStamp.length() - 1);

	std::string fullMessage(std::string("[") + timeStamp + "] " + message);
	std::cout << fullMessage << std::endl;
	_history.push_back(fullMessage);
	
}
