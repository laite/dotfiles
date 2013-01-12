/*										
 * helpers.cpp	
 * (c) Markus Klinga
 * 
 */

#include "helpers.h"
#include <ctime>

std::string Helpers::ParseShortTime(long seconds)
{
	std::string helper("");
	int firstFound = 100;

	if (seconds < 0)
	{
		seconds *= (-1);
		helper += "-";
	}

	if (seconds > 365*24*60*60) {
		helper += std::to_string(seconds/(365*24*60*60)) + "y ";
		seconds %= (365*24*60*60);
		firstFound = 1;
	}
	if (seconds > 30*24*60*60) {
		helper += std::to_string(seconds/(30*24*60*60)) + "m ";
		seconds %= (30*24*60*60);
		firstFound = std::min(firstFound, 2);
	}
	if ((seconds > 24*60*60) && (firstFound > 1)) {
		helper += std::to_string(seconds/(24*60*60)) + "d ";
		seconds %= (24*60*60);
		firstFound = std::min(firstFound, 3);
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
		if ((seconds > 60*60) && (firstFound > 2)) {
			helper += std::to_string(seconds/(60*60)) + "h ";
			seconds %= (60*60);
			firstFound = std::min(firstFound, 4);
		}
		if ((seconds > 60) && (firstFound > 3)) {
			helper += std::to_string(seconds/(60)) + "min ";
			seconds %= (60);
			firstFound = std::min(firstFound, 5);
		}
		if ((seconds > 0) && (firstFound > 4)) {
			helper += std::to_string(seconds) + "s";
		}
	}

	if (helper.size() == 0)
		helper = "0s";
	else // trim trailing whitespace
		helper = helper.substr(0, helper.find_last_not_of(" ") + 1);
	

	return helper;
}

std::string Helpers::ParseCustomDateTime(std::time_t *timePoint)
{
	std::string resultString("");
	std::string timeFormat = Global::Config.GetAppOptions().customDateTimeFormat;

	struct std::tm *timeInfo;
	timeInfo = localtime ( timePoint );

	bool hasFirst = 0;
	for (std::string::const_iterator character = timeFormat.begin();
			character != timeFormat.end(); ++character)
	{
		if (*character == '%')
			hasFirst = ((hasFirst)? 0 : 1);
		else if (hasFirst)
		{
			hasFirst = 0;
			if (*character == 'd')
				resultString += std::to_string(timeInfo->tm_mday);
			if (*character == 'm')
				resultString += std::to_string(1+timeInfo->tm_mon);
			if (*character == 'y')
				resultString += std::to_string(timeInfo->tm_year%100);
			if (*character == 'Y')
				resultString += std::to_string(1900+timeInfo->tm_year);
			if (*character == 'H')
				resultString += Helpers::AddLeadingZero(std::to_string(timeInfo->tm_hour));
			if (*character == 'M')
				resultString += Helpers::AddLeadingZero(std::to_string(timeInfo->tm_min));
		}
		else
			resultString += *character;
	}

	return resultString;
}

std::string Helpers::ParseLongTime(std::chrono::system_clock::time_point timePoint)
{
	std::time_t time_tPoint = std::chrono::system_clock::to_time_t(timePoint);
	std::string formattedString;

	if (Global::Config.GetAppOptions().useCustomDateTimeFormat)
		formattedString = Helpers::ParseCustomDateTime(&time_tPoint);
	else
	{
		formattedString = ctime(&time_tPoint);
		formattedString = formattedString.substr(0, formattedString.length() - 1); // remove \n from the end
	}

	return formattedString;
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

std::string Helpers::GetTimeFrameTypeName(int timeFrame)
{
	std::vector<std::string> goalNames { "day", "week", "month"};

	if (goalNames.size() > timeFrame)
		return goalNames.at(timeFrame);
	else
		return "[unknown]";
}

int Helpers::GetTimeFrameModifier(int timeFrame)
{
	std::vector<int> modifiers { 1, 7, 30 };
	
	if (modifiers.size() > timeFrame)
		return modifiers.at(timeFrame);
	else
		return 1;
}

std::string Helpers::GetParsedSince(std::chrono::system_clock::time_point then)
{
	return Helpers::ParseShortTime(Helpers::GetSecondsSince(then));
}

long Helpers::GetSecondsSince(std::chrono::system_clock::time_point then)
{
	std::chrono::duration<double> timeAgo = std::chrono::duration_cast< std::chrono::duration<double> >(std::chrono::steady_clock::now() - then);
	
	return timeAgo.count();
}
std::string Helpers::GetBooleanString(bool value)
{
	return ((value)? "true" : "false");
}
