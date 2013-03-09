/*										
 * global.cpp	
 * (c) Markus Klinga
 * 
 */

#include "global.h"

/*
 *  LogClass
 */


void LogClass::Add(std::string message, bool debugOnly)
{
	if ((debugOnly) && (!Global::debugMode))
		return;

	std::chrono::system_clock::time_point today = std::chrono::system_clock::now();
	std::time_t tt = std::chrono::system_clock::to_time_t ( today );
	std::string timeStamp(ctime(&tt));
	timeStamp = timeStamp.substr(0, timeStamp.length() - 1);

	std::string fullMessage(std::string("[") + timeStamp + "] " + message);
	std::cout << fullMessage << std::endl;
	_history.push_back(fullMessage);
	
}


/*
 *  UniqueNumber
 */

UniqueNumber::UniqueNumber()
	: _lastNumber(0)
	, _amountOfNumbers(0)
{
	
}

unsigned int UniqueNumber::GenerateNumber()
{
	unsigned int newNumber;

	// if there is released numbers, we give one of them
	if (_releasedNumbers.size() > 0)
	{
		newNumber = _releasedNumbers.front();
		_releasedNumbers.pop();
	}
	else
	{
		// otherwise we return next number available
		newNumber = ++_lastNumber;
	}

	return newNumber;
}

void UniqueNumber::ReleaseNumber(unsigned int num)
{
	_releasedNumbers.push(num);
}
