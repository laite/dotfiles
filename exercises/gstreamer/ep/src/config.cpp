/*										
 * config.cpp	
 * (c) Markus Klinga
 * 
 */

#include "config.h"
#include "global.h"

Options Global::options;

Options::Options()
{
	_appOptions.repeatMode = AppOptions::REPEAT_ALL;
	_appOptions.playbackButtonLabels = false;
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

void Options::SaveOptions(std::string file)
{
	
}

std::string Options::GetSettingsFolder()
{
	std::string value(".");
	char const* tmp = getenv("HOME");

	if (tmp != NULL)
	{
		value = tmp;
		value += "/.config/laite/ep";
	}

	return value;
}

