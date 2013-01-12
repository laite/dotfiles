/*										
 * data.h	
 * (c) Markus Klinga
 * 
 * DataBase class declaration
 */

#ifndef TIMETRACKER_DATA_H
#define TIMETRACKER_DATA_H

#include <gtkmm.h>
#include <set>
#include <string>
#include <chrono>

class ModelColumns;

class UniqueID
{
	public:
		UniqueID();
		unsigned int GenerateID();
		void ReleaseID(unsigned int);

	private:

		unsigned int _lastID;
		std::set<unsigned int> _releasedIDs;
		unsigned int _amountOfIDs;
};

struct DataItem 
{
	DataItem();
	unsigned int ID; // unique identifier in DataBase, only created when dataItem is put in db
	std::string name; // short name of data item
	std::string description; // longer definition
	int percentage; // [0..100], basically current/goal
	bool continuous; // whether data is measured continuously (seconds) or by instances
	bool inverse; // do we count to or from, default false

	long goal; // seconds per day OR instances per day, depending on item type (bool continuous)
	int goalTimeFrame; // GOAL_TIMEFRAME_DAY, GOAL_TIMEFRAME_WEEK or GOAL_TIMEFRAME_MONTH

	std::chrono::system_clock::time_point firstRunTime; // time of first run
	std::chrono::system_clock::time_point lastRunTime; // time of first run

	std::map<std::chrono::system_clock::time_point, std::chrono::system_clock::time_point> history;

	// this is just a helper that calls function below with same value twice as parametres
	void AddNewRun(std::chrono::system_clock::time_point);
	void AddNewRun(std::chrono::system_clock::time_point, std::chrono::system_clock::time_point);
	void ChangeEndPoint(std::chrono::system_clock::time_point, std::chrono::system_clock::time_point);

	void CalculatePercentage();
	long GetSecondsFromTimeFrame() const;

	int GetTimes() const; // returns number of runs (aka history.size())
	long GetTotal() const; // returns elapsed time from history (in seconds)
	std::string GetGoalString() const;

	long GetDifference() const;
	long GetSecondsSinceFirstRun() const;
	long GetAveragePerTimeFrame() const;
	std::string GetAveragePerTimeFrameString() const;
	long GetAverageRunLength() const;
};

class DataBase 
{
	public:
		
		/*
		 *  Constructors & Destructors
		 */
		
		DataBase();
		~DataBase();
		
		/*
		 *  Public Functions
		 */

		void AddItemToDataBase(DataItem&);
		void RemoveItemFromDataBase(unsigned int);
		
		int GetSize();
		bool IsIn(unsigned int ID);
		DataItem& GetItem(std::map<unsigned int, DataItem>::iterator wanted);
		DataItem& GetItem(unsigned int);
		DataItem* GetIDDataCopy(unsigned int);

		const std::map<unsigned int, DataItem>& GetData();

		void UpdateItemStats(unsigned int);

	private:

		void _Load();
		void _Save();
		std::string _GetSettingsFolder();
		std::vector<std::string> _ReadConfigFile();

		unsigned int _CalculatePercentage(const DataItem&);

		std::map<unsigned int, DataItem> _data;
		UniqueID _uniqueID;
};

#endif /* end DATA_H */
