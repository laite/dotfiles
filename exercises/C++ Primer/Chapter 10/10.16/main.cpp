// Ex 10.16: map::find

#include "../../helpers.h"

int main()
{
	map<string, vector<int> > readings;
	map<string, vector<int> >::iterator iter = readings.find("Kiira Korpi");

	if (iter != readings.end())
		cout << "Kiira!" << endl;
	else
		cout << "No Kiira for you." << endl;

	return 0;
}
