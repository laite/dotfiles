/*										
 * data.cpp	
 * (c) Markus Klinga
 * 
 * Definition of DataBase class
 */

#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>

#include "log.h"
#include "data.h"
#include "treedata.h"
#include "config.h"
#include "helpers.h"


/*
 *  UniqueID
 */


UniqueID::UniqueID():
	_lastID(0),
	_amountOfIDs(0)
{
	Log.Add("UniqueID holder created");
}

unsigned int UniqueID::GenerateID()
{
	// by default give next integer
	unsigned int newID;

	// if something has been released we'll use that instead
	if (_releasedIDs.size() > 0)
	{
		std::set<unsigned int>::iterator releasedIter = _releasedIDs.begin();
		newID = *releasedIter;
		_releasedIDs.erase(releasedIter);

		Log.Add("Got UniqueId from _releasedIDs: " + std::to_string(_releasedIDs.size()) + " left");
	}
	else
	{
		newID = ++_lastID;
	}

	return newID;
}

void UniqueID::ReleaseID(unsigned int newlyReleasedID)
{
	// _releasedIDs takes care of possible duplicates by being a std::set
	_releasedIDs.insert(newlyReleasedID);
}


/*
 *  DataItem
 */


DataItem::DataItem():
	ID(0), name("[empty]"), description("[empty]"), percentage(0), continuous(false), inverse(false), 
	times(0), elapsedTime(0), goal(0), goalTimeFrame(0)
{

}

void DataItem::CalculatePercentage()
{
	std::chrono::duration<int,std::ratio<1> > timeAgo = std::chrono::duration_cast< std::chrono::duration<int,std::ratio<1> > >(std::chrono::steady_clock::now() - firstTime);
	
	long hasBeen = timeAgo.count(); // this is in seconds
	long worked = elapsedTime; // and so is this
	long cGoal = goal;
	double supposedRatio, workedRatio;

	if ((cGoal == 0) || (hasBeen == 0))
	{
		Log.Add("No cGoal or TimeSpent");
		percentage = 0;
		return;
	}

	if (continuous)
	{
		supposedRatio = 1.0*cGoal / (GetSecondsFromTimeFrame()); // calculate ratio to be 'percents of TIMEFRAME'
		workedRatio = 1.0*worked / hasBeen; // and completed ratio
	}
	else
	{
		// format for ratios here is: instances / day
		supposedRatio = 1.0*cGoal / (1.0*GetSecondsFromTimeFrame() / (24*60*60));
		workedRatio = 1.0*times / (1.0*hasBeen / (24*60*60));
	}

	double result = (1.0*workedRatio) / supposedRatio;

	if (result > 1)
		result = 1;
	else if (result < 0)
		result = 0;

	percentage = std::round(100*result);
}

long DataItem::GetSecondsFromTimeFrame() const
{
	if (goalTimeFrame == Global::GOAL_TIMEFRAME_WEEK)
		return (7*24*60*60);
	else if (goalTimeFrame == Global::GOAL_TIMEFRAME_MONTH)
		return (30*24*60*60);
	else
		return (24*60*60); // use GOAL_TIMEFRAME_DAY also as a fallback
}

/*
 *  DataBase
 */


DataBase::DataBase()
{
	_Load();
}

DataBase::~DataBase()
{
	_Save();
}

void DataBase::_Load()
{
	std::vector<DataItem> loadedData = Config.GetSavedData();

	for (std::vector<DataItem>::iterator dataIter = loadedData.begin();
			dataIter != loadedData.end(); ++dataIter)
		AddItemToDataBase(*dataIter);

	Log.Add("Loaded " + std::to_string(_data.size()) + " items");

}

void DataBase::_Save()
{

}

void DataBase::AddItemToDataBase(DataItem &item)
{
	unsigned int newID = _uniqueID.GenerateID();
	item.CalculatePercentage();
	Log.Add("Added item " + std::to_string(newID) + ". " + item.name);

	item.ID = newID; // we don't care if DataItem already has an ID
	_data.insert(std::make_pair(newID, item));
}

void DataBase::RemoveItemFromDataBase(unsigned int removableID)
{
	_data.erase(removableID);
	_uniqueID.ReleaseID(removableID);
}

int DataBase::GetSize()
{
	return _data.size();
}

bool DataBase::IsIn(unsigned int ID)
{
	return (_data.find(ID) != _data.end());
}

DataItem& DataBase::GetItem(unsigned int ID)
{
	return _data.find(ID)->second;
}

DataItem& DataBase::GetItem(std::map<unsigned int, DataItem>::iterator wanted)
{
	return wanted->second;
}

// Get specific DataItem from DataBase
DataItem* DataBase::GetIDDataCopy(unsigned int ID)
{
	std::map<unsigned int, DataItem>::iterator wantedIDIter = _data.find(ID);
	Log.Add("Looking for ID = " + std::to_string(ID));

	if (wantedIDIter != _data.end())
		return &wantedIDIter->second;
	else
	{
		Log.Add("ID = " + std::to_string(ID) + " was Not Found!");
		return NULL;
	}
}

const std::map<unsigned int, DataItem>& DataBase::GetData()
{
	return _data;
}

void DataBase::UpdateItemStats(unsigned int ID)
{
	if (!IsIn(ID))
		return;

	_data[ID].CalculatePercentage();
}

