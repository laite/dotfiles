/*										
 * helpers.h	
 * (c) Markus Klinga
 * 
 */

#ifndef TIMETRACKER_HELPERS_H
#define TIMETRACKER_HELPERS_H

#include <string>

namespace Helpers
{
	extern std::string ParseShortTime(long seconds);
}

namespace Global
{
	extern bool debugMode;
}

#endif /* end TIMETRACKER_HELPERS_H */
