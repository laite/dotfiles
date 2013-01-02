/*										
 * helpers.cpp	
 * (c) Markus Klinga
 * 
 */

#include "helpers.h"

std::string Helpers::ParseShortTime(long seconds)
{
	std::string helper("");
	if (seconds > 365*24*60*60) {
		helper += std::to_string(seconds/(365*24*60*60)) + "y ";
		seconds %= (365*24*60*60);
	}
	if (seconds > 30*24*60*60) {
		helper += std::to_string(seconds/(30*24*60*60)) + "m ";
		seconds %= (30*24*60*60);
	}
	if (seconds > 24*60*60) {
		helper += std::to_string(seconds/(24*60*60)) + "d ";
		seconds %= (24*60*60);
	}

	if (Global::Config.GetAppOptions().useShortTimeFormat)
	{
		if (seconds > 0)
		{
			helper += Helpers::AddLeadingZero(std::to_string((seconds/(60*60)))) + ":";
			seconds %= (60*60);
			helper += Helpers::AddLeadingZero(std::to_string((seconds/(60)))) + ":";
			seconds %= (60);
			helper += Helpers::AddLeadingZero(std::to_string(seconds));
		}
	}
	else
	{
		if (seconds > 60*60) {
			helper += std::to_string(seconds/(60*60)) + "h ";
			seconds %= (60*60);
		}
		if (seconds > 60) {
			helper += std::to_string(seconds/(60)) + "min ";
			seconds %= (60);
		}
		if (seconds > 0) {
			helper += std::to_string(seconds) + "s ";
		}
	}

	if (helper.size() == 0)
		helper = "n/a";

	return helper;
}

std::string Helpers::TruncateToString(double number, unsigned int prec)
{
	std::ostringstream ss;
	ss << std::fixed << std::setprecision(prec) << number;
	return ss.str();
}

std::string Helpers::AddLeadingZero(std::string originalString)
{
	if (originalString.size() == 1)
		return std::string(1,'0').append(originalString);
	else 
		return originalString;
}
