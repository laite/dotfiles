/*										
 * config.cpp	
 * (c) Markus Klinga
 * 
 */

#include <string>
#include <vector>
#include <fstream>
#include <boost/filesystem.hpp>

#include "config.h"
#include "log.h"
#include "data.h"
#include "helpers.h"


/*
 *  AppOptions
 */

AppOptions::AppOptions():
	useShortTimeFormat(false), noFunnyAverages(true)
{

}


/*
 *  ConfigClass
 */


ConfigClass::ConfigClass(std::string configFile):
	_configFileNameWithoutPath(configFile)
{
	_configFileFullName = _GetSettingsFolder() + "/" + _configFileNameWithoutPath;

	_configDataNames[DATAITEM_NAME] = "name";
	_configDataNames[DATAITEM_DESCRIPTION] = "description";
	_configDataNames[DATAITEM_TIMES] = "times";
	_configDataNames[DATAITEM_CONTINUOUS] = "continuous";
	_configDataNames[DATAITEM_INVERSE] = "inverse";
	_configDataNames[DATAITEM_ELAPSED_TIME] = "elapsed_time";
	_configDataNames[DATAITEM_GOAL] = "goal";
	_configDataNames[DATAITEM_GOAL_FRAME] = "goal_frame";
	_configDataNames[DATAITEM_FIRST_TIME] = "first_time";
	_configDataNames[DATAITEM_LAST_TIME] = "last_time";

	Global::Log.Add("Created ConfigClass.");
}

/*
 *  Destructor
 */

ConfigClass::~ConfigClass()
{

}

/*
 *  _GetSettingsFolder()
 *
 *  Return: 
 *  	"/home/USERNAME/.config/timetracker" or "."  (if there is no $HOME to be found)
 */

std::string ConfigClass::_GetSettingsFolder()
{
	std::string value(".");
	char const* tmp = getenv("HOME");

	if (tmp != NULL)
	{
		value = tmp;
		value += "/.config/timetracker";
	}

	return value;
}

/*
 *  _ReadConfigFile()
 *
 *  Does:
 *  	Read configFileFullName into _rawConfigFileContents
 */

void ConfigClass::_ReadConfigFile()
{
	using namespace boost::filesystem;

	_rawConfigFileContents.clear(); // erase everything old

	try
	{
		path p(_configFileFullName);
		if (!exists(p))
			Global::Log.Add("No data file found");
		else
		{
			Global::Log.Add("Found data file!");
			std::ifstream file(_configFileFullName);

			std::string s;
			while (getline(file, s))
				_rawConfigFileContents.push_back(s);

			file.close();
		}
	}
	catch (const filesystem_error& ex)
	{
		Global::Log.Add(std::string("Critical: ") + ex.what());
	}
}

/*
 *  _ParseConfigFile()
 *
 *  Does:
 *  	Splits _rawConfigFileContents into _rawAppConfig and _rawDbConfig
 */

void ConfigClass::_ParseConfigFile()
{
	if (_rawConfigFileContents.size() == 0)
			return;

	_rawAppConfig.clear();
	_rawDbConfig.clear();

	int section(0);
	for (std::vector<std::string>::iterator contentsIter = _rawConfigFileContents.begin();
			contentsIter != _rawConfigFileContents.end(); ++contentsIter)
	{
		std::string line = *contentsIter;

		if ((line.length() == 0) || (line[0] == '#'))
			continue;
		else if (line[0] == '[')
			++section;
		else
		{
			if (section == 0) // this is error
				continue;
			else if (section == 1) // application settings
				_rawAppConfig.push_back(line);
			else if (section == 2) // DataBase
				_rawDbConfig.push_back(line);
			else // this is also an error
			{
				Global::Log.Add("ERROR (_ParseConfigFile): Too many sections found, some data may be not loaded properly!");
				continue;
			}
		}
	}
}

/*
 *  _BuildConfigFile()
 *
 *  Does:
 *  	Populates _rawAppConfig and _rawDbConfig with current data
 */

void ConfigClass::_BuildConfigFile(DataBase *db)
{
	_rawConfigFileContents.clear(); // clear old data

	_FetchAppConfig();
	_FetchDBConfig(db);
}

/*
 *  _WriteConfigFile()
 *
 *  Does:
 *  	Writes all data to config file
 */

void ConfigClass::_WriteConfigFile()
{
	using namespace boost::filesystem;

	_rawConfigFileContents.insert(_rawConfigFileContents.end(), _rawAppConfig.begin(), _rawAppConfig.end());
	_rawConfigFileContents.insert(_rawConfigFileContents.end(), _rawDbConfig.begin(), _rawDbConfig.end());

	try
	{
		path directory(_GetSettingsFolder());
		if (!exists(directory))
			create_directory(directory);

		std::ofstream file(_configFileFullName);

		for (std::vector<std::string>::iterator contentIter = _rawConfigFileContents.begin();
				contentIter != _rawConfigFileContents.end(); ++contentIter)
		{
			file << *contentIter << "\n";
		}

		file.close();
	}
	catch (const filesystem_error& ex)
	{
		Global::Log.Add(std::string("Critical: ") + ex.what());
	}
	
	Global::Log.Add("Saved " + _configFileFullName);
}

/*
 * 	GetSavedData()
 *
 * 	Does:
 * 		Parses DataItems from _rawDbConfig
 * 	Return:
 * 		Vector of DataItems parsed from data file
 */

std::vector<DataItem> ConfigClass::GetSavedData()
{
	std::vector<DataItem> loaded;
	std::vector<DataItem>::iterator dataIter;
	std::string change = ">> DataItem";

	if (_rawDbConfig.size() != 0)
	{
		for (std::vector<std::string>::iterator lineIter = _rawDbConfig.begin();
				lineIter != _rawDbConfig.end(); ++lineIter)
		{
			std::string line = *lineIter;

			if((line.size() >= change.size()) && (line.substr(0, change.size()) == change))
			{
				DataItem newItem;
				dataIter = loaded.insert(loaded.end(), newItem);
			}
			else
			{
				if (_IsLineDbItem(line, DATAITEM_NAME))
					dataIter->name = line.substr(_configDataNames[DATAITEM_NAME].size() + 3);
				else if (_IsLineDbItem(line, DATAITEM_DESCRIPTION))
					dataIter->description = line.substr(_configDataNames[DATAITEM_DESCRIPTION].size() + 3);
				else if (_IsLineDbItem(line, DATAITEM_TIMES))
					dataIter->times = std::stoi(line.substr(_configDataNames[DATAITEM_TIMES].size() + 3));
				else if (_IsLineDbItem(line, DATAITEM_CONTINUOUS))
				{
					std::string tempValue = line.substr(_configDataNames[DATAITEM_CONTINUOUS].size() + 3);
					dataIter->continuous = (tempValue == "true"? 1 : 0);
				}
				else if (_IsLineDbItem(line, DATAITEM_INVERSE))
				{
					std::string tempValue = line.substr(_configDataNames[DATAITEM_INVERSE].size() + 3);
					dataIter->inverse = (tempValue == "true"? 1 : 0);
				}
				else if (_IsLineDbItem(line, DATAITEM_ELAPSED_TIME))
					dataIter->elapsedTime = std::stol(line.substr(_configDataNames[DATAITEM_ELAPSED_TIME].size() + 3));
				else if (_IsLineDbItem(line, DATAITEM_GOAL))
					dataIter->goal = std::stol(line.substr(_configDataNames[DATAITEM_GOAL].size() + 3));
				else if (_IsLineDbItem(line, DATAITEM_GOAL_FRAME))
					dataIter->goalTimeFrame = std::stoi(line.substr(_configDataNames[DATAITEM_GOAL_FRAME].size() + 3));
				else if (_IsLineDbItem(line, DATAITEM_FIRST_TIME))
				{
					long savedTime = std::stol(line.substr(_configDataNames[DATAITEM_FIRST_TIME].size() + 3));
					std::chrono::duration<int> since(savedTime);
					dataIter->firstRunTime = std::chrono::system_clock::time_point(since);
				}
				else if (_IsLineDbItem(line, DATAITEM_LAST_TIME))
				{
					long savedTime = std::stol(line.substr(_configDataNames[DATAITEM_LAST_TIME].size() + 3));
					std::chrono::duration<int> since(savedTime);
					dataIter->lastRunTime = std::chrono::system_clock::time_point(since);
				}
			}
		}
	}

	Global::Log.Add("GetSavedData: " + std::to_string(loaded.size()));
	
	return loaded;
}

/*
 *  _IsLineDbItem()
 *
 *  Does:
 *  	Checks whether line starts with _configDataNames[item]
 *  Return:
 *  	True or false
 */

bool ConfigClass::_IsLineDbItem(std::string line, int item)
{
	std::string compareItem = _configDataNames[item] + " = ";
	return ((line.size() >= compareItem.size())
				&& 
			(line.substr(0, compareItem.size()) == compareItem));
}

/*
 *  SaveEverything()
 *
 *  Does:
 *  	Builds current config and saves it into a file
 */

void ConfigClass::SaveEverything(DataBase *db)
{
	_BuildConfigFile(db);
	_WriteConfigFile();

}

/*
 *  LoadConfig()
 *
 *  Does:
 *  	Read and parse config from file
 */

void ConfigClass::LoadConfig()
{
	_ReadConfigFile();
	_ParseConfigFile();
}


/*
 * ChangeFileName()
 *
 * Does:
 *  	Change name of config file
 */

void ConfigClass::ChangeFileName(std::string newName)
{
	if (newName.size() == 0)
		return;

	_configFileNameWithoutPath = newName;
	_configFileFullName = _GetSettingsFolder() + "/" + _configFileNameWithoutPath;
}

/*
 *  _FetchAppConfig()
 *
 *  Does:
 *  	Fetches current application settings into _rawAppConfig
 */

void ConfigClass::_FetchAppConfig()
{
	Global::Log.Add("Fetching App Settings");

	std::vector<std::string> appConfig;


	// App Configs go here
	appConfig.push_back("[Application]");
	appConfig.push_back("example_key = this");


	_rawAppConfig = appConfig;
}

/*
 *  _FetchDbConfig()
 *
 *  Does:
 *  	Fetches current DataItems into _rawDbConfig
 */

void ConfigClass::_FetchDBConfig(DataBase *db)
{
	std::vector<std::string> dbConfig { "[Database]" };

	std::map<unsigned int, DataItem> dataItems = db-> GetData();
	Global::Log.Add("Fetching DataBase items (Found " + std::to_string(dataItems.size()) + ")");

	if (dataItems.size() != 0)
	{
		for (std::map<unsigned int, DataItem>::const_iterator dataIter = dataItems.begin();
				dataIter != dataItems.end(); ++dataIter)
		{
			dbConfig.push_back(">> DataItem " + std::to_string(dataIter->second.ID));
			dbConfig.push_back(_configDataNames[DATAITEM_NAME] + " = " + dataIter->second.name);
			dbConfig.push_back(_configDataNames[DATAITEM_DESCRIPTION] + " = " + dataIter->second.description);
			dbConfig.push_back(_configDataNames[DATAITEM_TIMES] + " = " + std::to_string(dataIter->second.times));
			dbConfig.push_back(std::string(_configDataNames[DATAITEM_CONTINUOUS]) + " = " + (dataIter->second.continuous? "true" : "false"));
			dbConfig.push_back(std::string(_configDataNames[DATAITEM_INVERSE]) + " = " + (dataIter->second.inverse? "true" : "false"));
			dbConfig.push_back(_configDataNames[DATAITEM_ELAPSED_TIME] + " = " + std::to_string(dataIter->second.elapsedTime));
			dbConfig.push_back(_configDataNames[DATAITEM_GOAL] + " = " + std::to_string(dataIter->second.goal));
			dbConfig.push_back(_configDataNames[DATAITEM_GOAL_FRAME] + " = " + std::to_string(dataIter->second.goalTimeFrame));

			std::chrono::duration<int> dur = std::chrono::duration_cast<std::chrono::duration<int>>(dataIter->second.firstRunTime.time_since_epoch());
			dbConfig.push_back(_configDataNames[DATAITEM_FIRST_TIME] + " = " + std::to_string(dur.count()));
			
			dur = std::chrono::duration_cast<std::chrono::duration<int>>(dataIter->second.lastRunTime.time_since_epoch());
			dbConfig.push_back(_configDataNames[DATAITEM_LAST_TIME] + " = " + std::to_string(dur.count()));
		}
	}

	_rawDbConfig = dbConfig;
}

AppOptions ConfigClass::GetAppOptions()
{
	return _appOptions;
}
