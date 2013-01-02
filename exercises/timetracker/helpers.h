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

namespace Helpers
{
	extern std::string ParseShortTime(long seconds);
	extern std::string TruncateToString(double number, unsigned int prec = 2);

}

namespace Global
{
	enum { GOAL_TIMEFRAME_DAY, GOAL_TIMEFRAME_WEEK, GOAL_TIMEFRAME_MONTH };

	extern bool debugMode;
}

#endif /* end TIMETRACKER_HELPERS_H */
