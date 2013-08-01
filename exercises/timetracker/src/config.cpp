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
 *
 *  AppOptions
 *
 */

AppOptions::AppOptions()
	: useShortTimeFormat(false)
	, autoSave(true)
	, useCustomDateTimeFormat(true)
	, customDateTimeFormat("%d.%m.%Y %H:%M")
	, defaultWindowSize(800, 450)
	, panedPosition(255)
{
	Global::Log.Add("Initialized AppOptions.");
}


/*
 *
 *  ConfigClass
 *
 */


ConfigClass::ConfigClass(std::string configFile):
	_configFileNameWithoutPath(configFile)
{
	_configFileFullName = _GetSettingsFolder() + "/" + _configFileNameWithoutPath;

	_configDataNames[DATAITEM_NAME] = "name";
	_configDataNames[DATAITEM_DESCRIPTION] = "description";
	_configDataNames[DATAITEM_CONTINUOUS] = "continuous";
	_configDataNames[DATAITEM_INVERSE] = "inverse";
	_configDataNames[DATAITEM_GOAL] = "goal";
	_configDataNames[DATAITEM_GOAL_FRAME] = "goal_frame";
	_configDataNames[DATAITEM_FIRST_TIME] = "first_time";
	_configDataNames[DATAITEM_LAST_TIME] = "last_time";
	_configDataNames[DATAITEM_HISTORY] = "history_item";
	_configDataNames[DATAITEM_FIXED_GOAL] = "fixed_goal";

	_configDataNames[APPOPTION_USE_SHORT_TIME_FORMAT] = "use_short_time_format";
	_configDataNames[APPOPTION_USE_CUSTOM_DATETIME_FORMAT] = "use_custom_datetime_format";
	_configDataNames[APPOPTION_CUSTOM_DATETIME_FORMAT] = "custom_datetime_format";
	_configDataNames[APPOPTION_AUTOSAVE] = "autosave";
	_configDataNames[APPOPTION_DEFAULT_WINDOW_SIZE_X] = "default_window_size_x";
	_configDataNames[APPOPTION_DEFAULT_WINDOW_SIZE_Y] = "default_window_size_y";
	_configDataNames[APPOPTION_PANED_POSITION] = "paned_position";

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
 *  	"/home/USERNAME/.config/laite/timetracker" or "."  (if there is no $HOME to be found)
 */

std::string ConfigClass::_GetSettingsFolder()
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
 *  GetSavedOptions()
 *
 *  Does:
 *  	Sets application options according to _rawAppConfig
 *  Return:
 *  	Bool: True if file was found and settings were successfully set
 */

bool ConfigClass::GetSavedOptions()
{

	if (_rawAppConfig.size() == 0)
		return false;

	for (std::vector<std::string>::iterator lineIter = _rawAppConfig.begin();
			lineIter != _rawAppConfig.end(); ++lineIter)
	{
		std::string line = *lineIter;

		if (_IsLineDbItem(line, APPOPTION_USE_SHORT_TIME_FORMAT))
		{
			std::string tempValue = line.substr(_configDataNames[APPOPTION_USE_SHORT_TIME_FORMAT].size() + 3);
			_appOptions.useShortTimeFormat = (tempValue == "true"? 1 : 0);
		}
		else if (_IsLineDbItem(line, APPOPTION_USE_CUSTOM_DATETIME_FORMAT))
		{
			std::string tempValue = line.substr(_configDataNames[APPOPTION_USE_CUSTOM_DATETIME_FORMAT].size() + 3);
			_appOptions.useCustomDateTimeFormat = (tempValue == "true"? 1 : 0);
		}
		else if (_IsLineDbItem(line, APPOPTION_CUSTOM_DATETIME_FORMAT))
			_appOptions.customDateTimeFormat = line.substr(_configDataNames[APPOPTION_CUSTOM_DATETIME_FORMAT].size() + 3);
		else if (_IsLineDbItem(line, APPOPTION_AUTOSAVE))
		{
			std::string tempValue = line.substr(_configDataNames[APPOPTION_AUTOSAVE].size() + 3);
			_appOptions.autoSave = (tempValue == "true"? 1 : 0);
		}
		else if (_IsLineDbItem(line, APPOPTION_DEFAULT_WINDOW_SIZE_X))
			_appOptions.defaultWindowSize.first = std::stoi(line.substr(_configDataNames[APPOPTION_DEFAULT_WINDOW_SIZE_X].size() + 3));
		else if (_IsLineDbItem(line, APPOPTION_DEFAULT_WINDOW_SIZE_Y))
			_appOptions.defaultWindowSize.second = std::stoi(line.substr(_configDataNames[APPOPTION_DEFAULT_WINDOW_SIZE_Y].size() + 3));
		else if (_IsLineDbItem(line, APPOPTION_PANED_POSITION))
			_appOptions.panedPosition = std::stoi(line.substr(_configDataNames[APPOPTION_PANED_POSITION].size() + 3));
		else 
		{
			Global::Log.Add("ERROR! Unknown line in _rawAppConfig!");
			Global::Log.Add("faulty line: " + line);
		}
	}

	Global::Log.Add("GetSavedOptions: success");

	return true;
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
				else if (_IsLineDbItem(line, DATAITEM_CONTINUOUS))
					dataIter->continuous = Helpers::ReadBoolFromString(line.substr(_configDataNames[DATAITEM_CONTINUOUS].size() + 3));
				else if (_IsLineDbItem(line, DATAITEM_INVERSE))
					dataIter->inverse = Helpers::ReadBoolFromString(line.substr(_configDataNames[DATAITEM_INVERSE].size() + 3));
				else if (_IsLineDbItem(line, DATAITEM_GOAL))
					dataIter->goal = std::stol(line.substr(_configDataNames[DATAITEM_GOAL].size() + 3));
				else if (_IsLineDbItem(line, DATAITEM_GOAL_FRAME))
					dataIter->goalTimeFrame = std::stoi(line.substr(_configDataNames[DATAITEM_GOAL_FRAME].size() + 3));
				else if (_IsLineDbItem(line, DATAITEM_FIRST_TIME))
					dataIter->firstRunTime = Helpers::ReadTimePointFromString(line.substr(_configDataNames[DATAITEM_FIRST_TIME].size() + 3));
				else if (_IsLineDbItem(line, DATAITEM_LAST_TIME))
					dataIter->lastRunTime = Helpers::ReadTimePointFromString(line.substr(_configDataNames[DATAITEM_LAST_TIME].size() + 3));
				else if (_IsLineDbItem(line, DATAITEM_HISTORY))
				{
					// history is defined as "history_item = FROM/TO"
					std::string value = line.substr(_configDataNames[DATAITEM_HISTORY].size() + 3);
					std::size_t middlePoint = value.find('/');

					if (middlePoint == std::string::npos) {
						Global::Log.Add("ERROR! Can't parse history item!");
						continue;
					}

					long beginTime = std::stol(value.substr(0, middlePoint));
					long endTime = std::stol(value.substr(middlePoint+1));
					std::chrono::duration<int> bSince(beginTime),eSince(endTime);
					dataIter->AddNewRun(std::chrono::system_clock::time_point(bSince),std::chrono::system_clock::time_point(eSince));
				}
				else 
				{
					Global::Log.Add("ERROR! Unknown line in _rawDbConfig!");
					Global::Log.Add("faulty line: " + line);
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

	GetSavedOptions();
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
	appConfig.push_back(_configDataNames[APPOPTION_USE_SHORT_TIME_FORMAT] + " = " + Helpers::GetBooleanString(_appOptions.useShortTimeFormat));
	appConfig.push_back(_configDataNames[APPOPTION_USE_CUSTOM_DATETIME_FORMAT] + " = " + Helpers::GetBooleanString(_appOptions.useCustomDateTimeFormat));
	appConfig.push_back(_configDataNames[APPOPTION_CUSTOM_DATETIME_FORMAT] + " = " + _appOptions.customDateTimeFormat);
	appConfig.push_back(_configDataNames[APPOPTION_DEFAULT_WINDOW_SIZE_X] + " = " + std::to_string(_appOptions.defaultWindowSize.first));
	appConfig.push_back(_configDataNames[APPOPTION_DEFAULT_WINDOW_SIZE_Y] + " = " + std::to_string(_appOptions.defaultWindowSize.second));
	appConfig.push_back(_configDataNames[APPOPTION_PANED_POSITION] + " = " + std::to_string(_appOptions.panedPosition));

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
			dbConfig.push_back(std::string(_configDataNames[DATAITEM_CONTINUOUS]) + " = " + Helpers::GetBooleanString(dataIter->second.continuous));
			dbConfig.push_back(std::string(_configDataNames[DATAITEM_INVERSE]) + " = " + Helpers::GetBooleanString(dataIter->second.inverse));
			dbConfig.push_back(_configDataNames[DATAITEM_GOAL] + " = " + std::to_string(dataIter->second.goal));
			dbConfig.push_back(_configDataNames[DATAITEM_GOAL_FRAME] + " = " + std::to_string(dataIter->second.goalTimeFrame));

			std::chrono::duration<int> runTimeDuration = std::chrono::duration_cast<std::chrono::duration<int>>(dataIter->second.firstRunTime.time_since_epoch());
			dbConfig.push_back(_configDataNames[DATAITEM_FIRST_TIME] + " = " + std::to_string(runTimeDuration.count()));
			
			runTimeDuration = std::chrono::duration_cast<std::chrono::duration<int>>(dataIter->second.lastRunTime.time_since_epoch());
			dbConfig.push_back(_configDataNames[DATAITEM_LAST_TIME] + " = " + std::to_string(runTimeDuration.count()));

			// write history
			typedef std::map<std::chrono::system_clock::time_point, std::chrono::system_clock::time_point> historyTypedef;
			for (historyTypedef::const_iterator historyIter = dataIter->second.history.begin();
					historyIter != dataIter->second.history.end(); ++historyIter)
			{
				std::chrono::duration<int> historyBeginPoint = std::chrono::duration_cast<std::chrono::seconds>(historyIter->first.time_since_epoch());
				std::chrono::duration<int> historyEndPoint = std::chrono::duration_cast<std::chrono::duration<int>>(historyIter->second.time_since_epoch());
				dbConfig.push_back(_configDataNames[DATAITEM_HISTORY] + " = " + std::to_string(historyBeginPoint.count()) + "/" + std::to_string(historyEndPoint.count()));
			}
		}
	}

	_rawDbConfig = dbConfig;
}

AppOptions& ConfigClass::SetAppOptions()
{
	return _appOptions;
}

const AppOptions& ConfigClass::GetAppOptions() const
{
	return _appOptions;
}
