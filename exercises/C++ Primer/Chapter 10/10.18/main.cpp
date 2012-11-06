// Ex 10.18: families in the map
// ************************************
// Requires C++11 - support to compile!
// e.g. g++ -std=c++0x main.cpp
// ************************************

#include "../../helpers.h"

inline void PrintHelpMessage()
{
	cout << endl;
	cout << " * Please give query or exit pressing [Ctrl+d]: " << endl;
	cout << " * Type 'list' for all names" << endl;
	cout << " > " << flush;
}

inline void PrintResult(string result)
{
	cout << endl << " # " << result << " #" << endl;
}

int main()
{
	// map key is family surname
	// value consists of first names
	map<string, vector<string> > targetFamilies;

	targetFamilies.insert(make_pair("Smith", vector<string> { "John", "Jesse" }));
	targetFamilies.insert(make_pair("Doe", vector<string> { "John", "Jane" }));
	targetFamilies.insert(make_pair("Nahapaseetimatopelatom", vector<string> { "Abu", "Nadia", "Tania", "Tonya", "Sonya" }));
	targetFamilies.insert(make_pair("Messier", vector<string> { "Mark"}));
	targetFamilies.insert(make_pair("Kurri", vector<string> { "Jari", "Vanessa", "Camilla" }));
	targetFamilies.insert(make_pair("Berlioz", vector<string> { "Stewart", "Pamela", "Carla" }));

	PrintHelpMessage();

	string surname;
	while (cin >> surname)
	{
		// list all surnames with 'list'
		if (surname == "list")
		{
			string list("List of all family names: ");
			map<string, vector<string> >::iterator familyNames = targetFamilies.begin();
			while (familyNames != targetFamilies.end())
			{
				list.append(familyNames++->first);
				if (familyNames != targetFamilies.end())
					list.append(", ");
			}
			PrintResult(list);
		}
		else
		{
			map<string, vector<string> >::iterator familyNames = targetFamilies.find(surname);
			if (familyNames != targetFamilies.end())
			{
				string familyMembers("Members in family " + surname + ": ");
				vector<string>::iterator firstNames = familyNames->second.begin();
				while (firstNames != familyNames->second.end())
				{
					familyMembers.append(*firstNames);
					if (++firstNames != familyNames->second.end())
						familyMembers.append(", ");
				}
				PrintResult(familyMembers);
			}
			else
				PrintResult("No family " + surname + " found");
		}

		PrintHelpMessage();
	}

	cout << endl;

	return 0;
}
