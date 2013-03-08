/*										
 * global.cpp	
 * (c) Markus Klinga
 * 
 */

#include "global.h"

Options Global::options;

Options::Options()
{
	_appOptions.repeatMode = AppOptions::REPEAT_ALL;
}

Options::~Options()
{

}

void Options::LoadOptions(std::string file)
{
	std::string configFile = GetSettingsFolder() + "/";

	if (file == "")
		configFile += "config";
	else
		configFile += file;

}

void Options::SaveOptions()
{
	
}

std::string Options::GetSettingsFolder()
{
	std::string value(".");
	char const* tmp = getenv("HOME");

	if (tmp != NULL)
	{
		value = tmp;
		value += "/.config/laite/timetracker";
	}

	return value;
}


/*
 *  LogClass
 */


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
