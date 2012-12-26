/*										
 * main.cpp	
 * (c) Markus Klinga
 * 
 * This file handles main function of TimeTracker
 */


#include "log.h"
#include "window.h"
#include "data.h"
#include <gtkmm/application.h>

LogClass Log;

int main(int argc, char *argv[])
{
	Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "org.gtkmm.example");

	DataBase db;
	MainWindow window(&db);

	Log.Add("Init ready, launching window.");

	return app->run(window);
}
