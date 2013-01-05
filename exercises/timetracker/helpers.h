/*										
 * helpers.h	
 * (c) Markus Klinga
 * 
 */

#ifndef TIMETRACKER_HELPERS_H
#define TIMETRACKER_HELPERS_H

#include <string>
#include <sstream>
#include <iomanip>
#include <chrono>
#include "config.h"
#include "log.h"

namespace Helpers
{
	extern std::string ParseLongTime(std::chrono::system_clock::time_point timePoint);
	extern std::string ParseShortTime(long seconds);
	extern std::string TruncateToString(double number, unsigned int prec = 2);

	// this adds leading zero to single digits only, everything else is bypassed
	extern std::string AddLeadingZero(std::string originalString);

	extern std::string GiveTimeFrameType(int timeFrame);
	extern int GetTimeFrameModifier(int timeFrame);

	extern std::string GetParsedSince(std::chrono::system_clock::time_point);
	extern long GetSecondsSince(std::chrono::system_clock::time_point);
}

namespace Global
{
	enum { GOAL_TIMEFRAME_DAY, GOAL_TIMEFRAME_WEEK, GOAL_TIMEFRAME_MONTH };

	extern bool debugMode;
	extern ConfigClass Config;
	extern LogClass Log;
}

#endif /* end TIMETRACKER_HELPERS_H */
