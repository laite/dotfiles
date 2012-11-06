// Ex 10.19: families in the map (extended from ex. 10.19)
// ***************************************
// requires -std=c++0x when compiling
// ***************************************

#include "../../helpers.h"

void PrintHelpMessage()
{
	cout << endl;
	cout << " * Please give query or press [Ctrl+d] to exit: " << endl;
	cout << " * Type 'list' for all names" << endl;
	cout << " > " << flush;
}

inline void PrintResult(string result) {
	cout << endl << " # " << result << " #" << endl;
}

int main()
{
	// map key is family surname
	// value consists of vector of pairs (firstname, birthdate)
	map<string, vector<pair<string, string> > > targetFamilies;
	targetFamilies.insert(make_pair("Doe", vector<pair<string, string> > { 
				make_pair("Jane", "180984-1477"), make_pair("John", "xx0984-1476")
		}));
	targetFamilies.insert(make_pair("Smith", vector<pair<string, string> > { 
				make_pair("Mike", "060606+211A"), make_pair("Jesse", "190991-9992")
		}));

	// write instructions
	PrintHelpMessage();

	string surname;
	while (cin >> surname)
	{
		// list all surnames with 'list'
		if (surname == "list")
		{
			string list("List of all family names: ");
			map<string, vector<pair<string, string> > >::iterator familyNames = targetFamilies.begin();
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
			map<string, vector<pair<string, string> > >::iterator familyNames = targetFamilies.find(surname);
			if (familyNames != targetFamilies.end())
			{
				string familyMembers("Members in family " + surname + ": ");
				vector<pair<string, string> >::iterator firstNames = familyNames->second.begin();
				while (firstNames != familyNames->second.end())
				{
					familyMembers.append(firstNames->first);
					familyMembers.append(" (" + firstNames->second + ")");
					if (++firstNames != familyNames->second.end())
						familyMembers.append(", ");
				}
				PrintResult(familyMembers);
			}
			else
				PrintResult("No family " + surname + " found");
		} // surname != list

		PrintHelpMessage();
	}

	cout << endl;

	return 0;
}
