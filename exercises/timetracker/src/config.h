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
	
	// Window default size
	std::pair<int, int> defaultWindowSize;

	//Divider position
	int panedPosition;
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
		bool GetSavedOptions();
		void SaveEverything(DataBase *db);
		void LoadConfig();

		void ChangeFileName(std::string newName);

		const AppOptions& GetAppOptions() const;
		AppOptions& SetAppOptions();

	private:
		
		// Data item type names' indices start from index 100
		enum { 
			DATAITEM_NAME = 100, DATAITEM_DESCRIPTION, DATAITEM_TIMES, DATAITEM_CONTINUOUS, DATAITEM_INVERSE,
			DATAITEM_ELAPSED_TIME, DATAITEM_GOAL, DATAITEM_GOAL_FRAME, DATAITEM_FIRST_TIME, DATAITEM_LAST_TIME,
			DATAITEM_HISTORY, DATAITEM_FIXED_GOAL
		};

		// AppOptions names' indices start from place 200 and go up
		enum {
			APPOPTION_USE_SHORT_TIME_FORMAT = 200, APPOPTION_USE_CUSTOM_DATETIME_FORMAT,
			APPOPTION_CUSTOM_DATETIME_FORMAT, APPOPTION_AUTOSAVE, APPOPTION_DEFAULT_WINDOW_SIZE_X,
			APPOPTION_DEFAULT_WINDOW_SIZE_Y, APPOPTION_PANED_POSITION
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
