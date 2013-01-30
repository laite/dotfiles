/*										
 * main.h	
 * (c) Markus Klinga
 * 
 */

#ifndef MAIN_H
#define MAIN_H

#include <string>
#include <iostream>
#include <vector>

class LogClass
{
	public:

		void Add(std::string, bool debugOnly = true);
		void DumpHistory(std::ostream &output = std::cout);

	private:

		std::vector<std::string> _history;
		
};

extern LogClass Log;

#endif /* end MAIN_H */
