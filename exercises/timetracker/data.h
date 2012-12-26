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
	DataItem(std::string pName, std::string pDescription, bool pContinuous, double pGoalTime);
	unsigned int ID; // unique identifier in DataBase, only created when dataItem is put in db
	std::string name; // short name of data item
	std::string description; // longer definition
	int percentage; // [0..100], basically current/goal
	bool continuous; // whether data is measured continuously (seconds) or by instances
	int times;

	long elapsedTime; // elapsed time in seconds
	int goalTime; // seconds per day

	std::chrono::steady_clock::time_point firstTime; // timePoint of first modification
	std::chrono::steady_clock::time_point lastTime; // timePoint of last modification

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

		std::map<unsigned int, DataItem> _data;
		UniqueID _uniqueID;
};

#endif /* end DATA_H */
