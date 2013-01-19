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
#include <algorithm>

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
	Global::Log.Add("UniqueID holder created");
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

		Global::Log.Add("Got UniqueId from _releasedIDs: " + std::to_string(_releasedIDs.size()) + " left");
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
	fixedGoal(false), goal(0), goalTimeFrame(Global::GOAL_TIMEFRAME_DAY)
{

}

void DataItem::CalculatePercentage()
{
	double result = (1.0*GetAveragePerTimeFrame()) / goal;

	if (inverse)
		result = 2 - result;

	result = std::min(std::max(result, 0.0), 1.0);

	percentage = std::round(100*result);
}

long DataItem::GetSurplus() const
{
	double hasBeenTimeFrames = static_cast<double>(GetSecondsSinceFirstRun())/(Helpers::GetTimeFrameModifier(goalTimeFrame)*24*60*60);
	long result = (goal*hasBeenTimeFrames)-GetTotal();

	return ((inverse)? (result) : (-result));
}

void DataItem::ChangeEndPoint(std::chrono::system_clock::time_point existingBeginPoint, std::chrono::system_clock::time_point newEndPoint)
{
	if (history.find(existingBeginPoint) == history.end())
		return;

	std::chrono::system_clock::time_point oldEndPoint = history[existingBeginPoint];
	history[existingBeginPoint] = newEndPoint;

	// calculate timespan changes (in seconds)
	std::chrono::duration<int> newTimeSpan = std::chrono::duration_cast<std::chrono::duration<int>>
		(newEndPoint - oldEndPoint);
}

void DataItem::AddNewRun(std::chrono::system_clock::time_point newBeginPoint, std::chrono::system_clock::time_point newEndPoint)
{
	if (this->history.find(newBeginPoint) != this->history.end())
		return;

	this->history[newBeginPoint] = newEndPoint;

	// there is bound to be at least one item since we just added one
	this->lastRunTime = (history.rbegin())->first;

	// Set also to first time if needed
	if (this->firstRunTime.time_since_epoch().count() == 0)
		this->firstRunTime = (history.rbegin())->first;
}

void DataItem::AddNewRun(std::chrono::system_clock::time_point point)
{
	AddNewRun(point, point);
}

int DataItem::GetTimes() const
{
	return history.size();
}

long DataItem::GetTotal() const
{
	if (!continuous)
		return history.size();
	
	typedef std::map<std::chrono::system_clock::time_point, std::chrono::system_clock::time_point> historyType;

	long total = 0;
	for (historyType::const_iterator historyIter = history.begin();
			historyIter != history.end(); ++historyIter)
	{
		std::chrono::duration<long> difference = std::chrono::duration_cast< std::chrono::duration<long> >(historyIter->second - historyIter->first);
		total += difference.count();
	}

	return total;
}

long DataItem::GetSecondsSinceFirstRun() const
{
	std::chrono::duration<double> timeAgo = std::chrono::duration_cast< std::chrono::duration<double> >(std::chrono::steady_clock::now() - firstRunTime);

	return timeAgo.count();
}

double DataItem::GetAveragePerTimeFrame() const
{
	// with fixed goals we don't care about time frames
	if (fixedGoal)
		return GetTotal();

	long totalAmount = (continuous)? GetTotal() : GetTimes();

	double hasBeenDays = static_cast<double>(GetSecondsSinceFirstRun())/(24*60*60);

	// if first timeframe has not yet passed, we'll just give everything and call it an average
	if (hasBeenDays < Helpers::GetTimeFrameModifier(goalTimeFrame))
		return totalAmount;
	else
	{
		double hasBeenTimeFrames = hasBeenDays/Helpers::GetTimeFrameModifier(goalTimeFrame);
		return totalAmount/hasBeenTimeFrames;
	}
}

std::string DataItem::GetParsedStringFromDataType(long item) const
{
	if (continuous)
		return Helpers::ParseShortTime(item);
	else
		return std::to_string(item);
}

long DataItem::GetAverageRunLength() const
{
	return GetTotal()/GetTimes();
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
	std::vector<DataItem> loadedData = Global::Config.GetSavedData();

	for (std::vector<DataItem>::iterator dataIter = loadedData.begin();
			dataIter != loadedData.end(); ++dataIter)
		AddItemToDataBase(*dataIter);

	Global::Log.Add("Loaded " + std::to_string(_data.size()) + " items");

}

void DataBase::_Save()
{

}

void DataBase::AddItemToDataBase(DataItem &item)
{
	unsigned int newID = _uniqueID.GenerateID();
	item.CalculatePercentage();
	Global::Log.Add("Added item " + std::to_string(newID) + ". " + item.name);

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
	Global::Log.Add("Looking for ID = " + std::to_string(ID));

	if (wantedIDIter != _data.end())
		return &wantedIDIter->second;
	else
	{
		Global::Log.Add("ID = " + std::to_string(ID) + " was Not Found!");
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

