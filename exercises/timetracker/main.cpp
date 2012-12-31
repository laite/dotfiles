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

LogClass Log;
ConfigClass Config;

int main(int argc, char *argv[])
{
	Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "org.gtkmm.timetracker");

	DataBase db;
	MainWindow window(&db);

	Log.Add("Init ready, launching window.");

	app->run(window);

	Config.SaveEverything(&db);

	return 0;
}
