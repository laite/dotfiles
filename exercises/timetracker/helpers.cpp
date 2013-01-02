/*										
 * helpers.cpp	
 * (c) Markus Klinga
 * 
 */

#include "helpers.h"

std::string Helpers::ParseShortTime(long seconds)
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

std::string Helpers::TruncateToString(double number, unsigned int prec)
{
	std::ostringstream ss;
	ss << std::fixed << std::setprecision(prec) << number;
	return ss.str();
}

