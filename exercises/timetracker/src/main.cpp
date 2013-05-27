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

LogClass Global::Log;
ConfigClass Global::Config;
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
			Global::Log.Add("Debug Mode enabled.");
		}

		// clear all parametres
		for (int i=1; i < argc; ++i)
			argv[i] = NULL;
		argc = 1;
	}

	std::string applicationName("org.gtkmm.timetracker");
	if (Global::debugMode)
	{
		Global::Config.ChangeFileName("debug");
		applicationName = "org.gtkmm.timetracker-debug";
	}

	Global::Config.LoadConfig();

	Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, applicationName);

	DataBase db;

	// Run mainwindow in its own scope, so it gets destroyed before saving settings
	{
		MainWindow window(&db);
	
		Global::Log.Add("Init ready, launching window.");
		app->run(window);
	}

	Global::Config.SaveEverything(&db);

	return 0;
}
