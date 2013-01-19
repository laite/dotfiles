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
	// parses given datetime according to appOption.customDateTimeFormat
	extern std::string ParseCustomDateTime(std::time_t *timePoint);

	// returns date according to global app options
	extern std::string ParseLongTime(std::chrono::system_clock::time_point timePoint);

	// returns short, 'elapsed time' type time (e.g. "3d 12h")
	extern std::string ParseShortTime(long seconds);

	// shows double variables with wanted precision
	extern std::string TruncateToString(double number, unsigned int prec = 2);

	// adds leading zero to single digits only, everything else is bypassed, note that parameter given is std::string
	extern std::string AddLeadingZero(std::string originalString);

	// returns timeframe as string, e.g. "week"
	extern std::string GetTimeFrameTypeName(int timeFrame);

	// returns timeframe as days, e.g. 7
	extern int GetTimeFrameModifier(int timeFrame);

	// helper that calls ParseShortTime with value given by GetSecondsSince
	extern std::string GetParsedSince(std::chrono::system_clock::time_point);

	// returns seconds since epoch for given time point
	extern long GetSecondsSince(std::chrono::system_clock::time_point);

	// returns "true" or "false" as string
	extern std::string GetBooleanString(bool value);

	// returns true or false as bool
	extern bool ReadBoolFromString(std::string);

	// returns time point from string that contains seconds since epoch
	extern std::chrono::system_clock::time_point ReadTimePointFromString(std::string sourceString);
}

namespace Global
{
	enum { GOAL_TIMEFRAME_DAY, GOAL_TIMEFRAME_WEEK, GOAL_TIMEFRAME_MONTH };

	extern bool debugMode;
	extern ConfigClass Config;
	extern LogClass Log;
}

#endif /* end TIMETRACKER_HELPERS_H */
