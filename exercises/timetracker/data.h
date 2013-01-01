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
	int times;

	long elapsedTime; // elapsed time in seconds
	int goalTime; // minutes per day

	std::chrono::system_clock::time_point firstTime; // timePoint of first modification
	std::chrono::system_clock::time_point lastTime; // timePoint of last modification

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
		
		DataItem* GetIDDataCopy(unsigned int);

		int GetSize();
		bool IsIn(unsigned int ID);
		DataItem& GetItem(std::map<unsigned int, DataItem>::iterator wanted);
		DataItem& GetItem(unsigned int);
		const std::map<unsigned int, DataItem>& GetData();

	private:

		void _Load();
		void _Save();
		std::string _GetSettingsFolder();
		std::vector<std::string> _ReadConfigFile();

		std::map<unsigned int, DataItem> _data;
		UniqueID _uniqueID;
};

#endif /* end DATA_H */
