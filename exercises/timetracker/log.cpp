/*										
 * log.cpp	
 * (c) Markus Klinga
 * 
 */

#include "log.h"
#include <ctime>
#include <ratio>
#include <chrono>

void LogClass::Add(std::string message)
{
	std::chrono::system_clock::time_point today = std::chrono::system_clock::now();
	std::time_t tt = std::chrono::system_clock::to_time_t ( today );
	std::string timeStamp(ctime(&tt));
	timeStamp = timeStamp.substr(0, timeStamp.length() - 1);

	std::string fullMessage(std::string("[") + timeStamp + "] " + message);
	std::cout << fullMessage << std::endl;
	_history.push_back(fullMessage);
}

void LogClass::DumpHistory(std::ostream &output)
{
	for (std::vector<std::string>::const_iterator historyIter = _history.begin();
			historyIter != _history.end(); ++historyIter)
	{
		output << *historyIter << std::endl;
	}
}
