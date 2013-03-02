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
	
	/*
	 *  Variables
	 */
	
	// unique identifier in DataBase, only created when dataItem is put in dataBase
	unsigned int ID;

	// short name of data item
	std::string name;

	// longer definition
	std::string description;

	// [0..100], basically current/goal
	int percentage;

	// whether data is measured continuously (seconds) or by instances
	bool continuous;

	// do we count to or from, default false
	bool inverse;

	// seconds per timeframe OR instances per timeframe, depending on item type (bool continuous)
	long goal;

	// GOAL_TIMEFRAME_DAY, GOAL_TIMEFRAME_WEEK or GOAL_TIMEFRAME_MONTH for timebased, GOAL_TIMEFRAME_NONE for fixed goal
	int goalTimeFrame;

	// time of first run
	std::chrono::system_clock::time_point firstRunTime;

	// time of last run
	std::chrono::system_clock::time_point lastRunTime;

	// history holds all runs' begin- and endpoints
	std::map<std::chrono::system_clock::time_point, std::chrono::system_clock::time_point> history;
	
	/*
	 *  Methods
	 */

	// returns true if goalTimeFrame is GOAL_TIMEFRAME_NONE
	bool HasFixedGoal() const;
	
	// this is just a helper that calls function below with same value twice as parametres
	void AddNewRun(std::chrono::system_clock::time_point);

	// adds new run to history (for instance-based dataitems both timepoints must be same)
	void AddNewRun(std::chrono::system_clock::time_point, std::chrono::system_clock::time_point);

	// change end point of an existing history item
	void ChangeEndPoint(std::chrono::system_clock::time_point, std::chrono::system_clock::time_point);

	// update internal variable 'percentage'
	void CalculatePercentage();

	// returns number of runs (aka history.size())
	int GetTimes() const;

	// returns elapsed time from history (in seconds) for continuous, instances for !continuous
	long GetTotal() const;

	// return item as parsed string (depending on 'continuous')
	std::string GetParsedStringFromDataType(double) const;

	// return surplus in seconds/instances
	double GetSurplus() const;

	// get seconds elapsed since first run
	long GetSecondsSinceFirstRun() const;

	// get average elapsed time/instances within time range
	// if fixedGoal is true, return GetTotal()
	double GetAveragePerTimeFrame() const;

	// returns average run in seconds
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
