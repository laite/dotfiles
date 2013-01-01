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
	std::string ParseShortTime(long seconds)
	{
		std::string helper("");
		if (seconds > 365*24*60*60)
		{
			helper += std::to_string(seconds/(365*24*60*60));
			helper += "y ";
			seconds %= (365*24*60*60);
		}
		if (seconds > 30*24*60*60)
		{
			helper += std::to_string(seconds/(30*24*60*60));
			helper += "m ";
			seconds %= (30*24*60*60);
		}
		if (seconds > 24*60*60)
		{
			helper += std::to_string(seconds/(24*60*60));
			helper += "d ";
			seconds %= (24*60*60);
		}
		if (seconds > 60*60)
		{
			helper += std::to_string(seconds/(60*60));
			helper += "h ";
			seconds %= (60*60);
		}
		if (seconds > 60)
		{
			helper += std::to_string((seconds/(60)));
			helper += "min ";
			seconds %= (60);
		}
		if (seconds > 0)
		{
			helper += std::to_string(seconds);
			helper += "s";
		}

		if (helper.size() == 0)
			helper = "n/a";

		return helper;
	}
}

#endif /* end TIMETRACKER_HELPERS_H */
