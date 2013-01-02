/*										
 * main.cpp	
 * (c) Markus Klinga
 * 
 * This file handles main function of TimeTracker
 */


#include <gtkmm/application.h>
#include <string>

#include "log.h"
#include "config.h"
#include "window.h"
#include "data.h"
#include "helpers.h"

LogClass Log;
ConfigClass Config;

bool Global::debugMode = false;

int main(int argc, char *argv[])
{
	
	/*
	 *  If there are some command line parametres,
	 *  we check them out and delete them before creating window
	 */
	
	if (argc > 1)
	{
		std::string param(argv[1]);
		if (param == "-d")
		{
			Global::debugMode = true;
			Log.Add("Debug Mode enabled.");
		}

		for (int i=1; i < argc; ++i)
			argv[i] = NULL;
		argc = 1;
	}

	Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "org.gtkmm.timetracker");

	DataBase db;
	MainWindow window(&db);

	Log.Add("Init ready, launching window.");

	app->run(window);

	Config.SaveEverything(&db);

	return 0;
}
