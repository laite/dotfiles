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
#include "config.h"
#include "log.h"

namespace Helpers
{
	extern std::string ParseShortTime(long seconds);
	extern std::string TruncateToString(double number, unsigned int prec = 2);

	// this adds leading zero to single digits only, everything else is bypassed
	extern std::string AddLeadingZero(std::string originalString);

	extern std::string GiveTimeFrameType(int timeFrame);
}

namespace Global
{
	enum { GOAL_TIMEFRAME_DAY, GOAL_TIMEFRAME_WEEK, GOAL_TIMEFRAME_MONTH };

	extern bool debugMode;
	extern ConfigClass Config;
	extern LogClass Log;
}

#endif /* end TIMETRACKER_HELPERS_H */
