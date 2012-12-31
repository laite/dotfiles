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
	_configDataNames[DATAITEM_GOAL_TIME] = "goal_time";
	_configDataNames[DATAITEM_FIRST_TIME] = "first_time";
	_configDataNames[DATAITEM_LAST_TIME] = "last_time";

	Log.Add("Created Config.");
	_ReadConfigFile();
	_ParseConfigFile();
}

ConfigClass::~ConfigClass()
{

}

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

void ConfigClass::_ReadConfigFile()
{
	using namespace boost::filesystem;

	_rawConfigFileContents.clear(); // erase everything old

	try
	{
		path p(_configFileFullName);
		if (!exists(p))
			Log.Add("No data file found");
		else
		{
			Log.Add("Found data file!");
			std::ifstream file(_configFileFullName);

			std::string s;
			while (getline(file, s))
				_rawConfigFileContents.push_back(s);

			file.close();
		}
	}
	catch (const filesystem_error& ex)
	{
		Log.Add(std::string("Critical: ") + ex.what());
	}
}

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
			else if (section == 1) // Header
			{
				Log.Add(line);
			}
			else if (section == 2) // application settings
			{
				_rawAppConfig.push_back(line);
			}
			else if (section == 3) // DataBase
			{
				_rawDbConfig.push_back(line);
			}
		}
	}
}

void ConfigClass::_BuildConfigFile(DataBase *db)
{
	_rawConfigFileContents.clear();
	_rawConfigFileContents.push_back("[Head]");
	_rawConfigFileContents.push_back("version = " + TIMETRACKER_VERSION);

	_FetchAppConfig();
	_FetchDBConfig(db);
}

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
		Log.Add(std::string("Critical: ") + ex.what());
	}
	
	Log.Add("Saved " + _configFileFullName);
}

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
				else if (_IsLineDbItem(line, DATAITEM_GOAL_TIME))
					dataIter->goalTime = std::stoi(line.substr(_configDataNames[DATAITEM_GOAL_TIME].size() + 3));
				else if (_IsLineDbItem(line, DATAITEM_FIRST_TIME))
				{
					long savedTime = std::stol(line.substr(_configDataNames[DATAITEM_FIRST_TIME].size() + 3));
					std::chrono::duration<int> since(savedTime);
					dataIter->firstTime = std::chrono::system_clock::time_point(since);
				}
				else if (_IsLineDbItem(line, DATAITEM_LAST_TIME))
				{
					long savedTime = std::stol(line.substr(_configDataNames[DATAITEM_LAST_TIME].size() + 3));
					std::chrono::duration<int> since(savedTime);
					dataIter->lastTime = std::chrono::system_clock::time_point(since);
				}
			}
		}
	}

	Log.Add("GetSavedData: " + std::to_string(loaded.size()));
	
	return loaded;
}

bool ConfigClass::_IsLineDbItem(std::string line, int item)
{
	return ((line.size() >= _configDataNames[item].size())
				&& 
			(line.substr(0, _configDataNames[item].size()) == _configDataNames[item]));
}

void ConfigClass::SaveEverything(DataBase *db)
{
	_BuildConfigFile(db);
	_WriteConfigFile();

}

void ConfigClass::_FetchAppConfig()
{
	Log.Add("Fetching App Settings");

	std::vector<std::string> appConfig;


	// App Configs go here
	appConfig.push_back("[Application]");
	appConfig.push_back("example_key = this");


	_rawAppConfig = appConfig;
}

void ConfigClass::_FetchDBConfig(DataBase *db)
{
	std::vector<std::string> dbConfig { "[Database]" };

	std::map<unsigned int, DataItem> dataItems = db-> GetData();
	Log.Add("Fetching DataBase items (Found " + std::to_string(dataItems.size()) + ")");

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
			dbConfig.push_back(_configDataNames[DATAITEM_GOAL_TIME] + " = " + std::to_string(dataIter->second.goalTime));

			std::chrono::duration<int> dur = std::chrono::duration_cast<std::chrono::duration<int>>(dataIter->second.firstTime.time_since_epoch());
			dbConfig.push_back(_configDataNames[DATAITEM_FIRST_TIME] + " = " + std::to_string(dur.count()));
			
			dur = std::chrono::duration_cast<std::chrono::duration<int>>(dataIter->second.lastTime.time_since_epoch());
			dbConfig.push_back(_configDataNames[DATAITEM_LAST_TIME] + " = " + std::to_string(dur.count()));
		}
	}

	_rawDbConfig = dbConfig;
}

