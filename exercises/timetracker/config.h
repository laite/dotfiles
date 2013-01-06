/*										
 * config.h	
 * (c) Markus Klinga
 * 
 * contains all configurations and saved data - related stuff
 */

#ifndef TIMETRACKER_CONFIG_H
#define TIMETRACKER_CONFIG_H

#include <string>
#include <vector>
#include <map>

class DataItem;
class DataBase;

const std::string TIMETRACKER_VERSION = "-0.1";

struct AppOptions
{
	AppOptions();

	// true: use hh:mm:ss instead of Xh Ymin Zs
	bool useShortTimeFormat;

	// true: use customTimeFormat for parsing date
	bool useCustomDateTimeFormat;
	std::string customDateTimeFormat;

	// true: save data automatically after each run
	bool autoSave;
	
};

class ConfigClass
{
	public:
		
		/*
		 *  Constructor
		 */
		
		ConfigClass(std::string configFile = "data");
		~ConfigClass();
		
		/*
		 *  Methods
		 */
		
		std::vector<DataItem> GetSavedData();
		void SaveEverything(DataBase *db);
		void LoadConfig();

		void ChangeFileName(std::string newName);

		AppOptions GetAppOptions();

	private:
		
		// Data item type names' indices
		enum { 
			DATAITEM_NAME, DATAITEM_DESCRIPTION, DATAITEM_TIMES, DATAITEM_CONTINUOUS, DATAITEM_INVERSE,
			DATAITEM_ELAPSED_TIME, DATAITEM_GOAL, DATAITEM_GOAL_FRAME, DATAITEM_FIRST_TIME, DATAITEM_LAST_TIME,
			DATAITEM_HISTORY
		};

		/*
		 *  Private Methods
		 */
		
		void _ReadConfigFile(); // read from filesystem to _rawConfigFileContents
		void _ParseConfigFile(); // handle the raw data
		
		void _BuildConfigFile(DataBase *db); // prepare for saving
		void _WriteConfigFile(); // write file to disk

		void _FetchAppConfig(); // saves properly formatted appconfig to _rawAppConfig
		void _FetchDBConfig(DataBase *db); // saves properly formatted database to _rawDbConfig

		bool _IsLineDbItem(std::string line, int item);
		std::string _GetSettingsFolder();

		/*
		 *  Private Variables
		 */

		std::map<int, std::string> _configDataNames;

		std::string _configFileNameWithoutPath; // this is a constructor parameter
		std::string _configFileFullName; // this is full path to file + filename
		std::vector<std::string> _rawConfigFileContents;
		std::vector<std::string> _rawAppConfig;
		std::vector<std::string> _rawDbConfig;
		
		AppOptions _appOptions;
};

extern ConfigClass Config;

#endif /* end CONFIG_H */
