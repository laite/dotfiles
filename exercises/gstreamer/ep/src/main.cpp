#include <gtkmm.h>
#include <gstreamermm.h>
#include <iostream>
#include <string>

#include "backend.h"
#include "window.h"
#include "global.h"

bool Global::debugMode = true;
LogClass Global::Log;
Engine Global::player;

int main(int argc, char* argv[]) 
{
	Gst::init(); 

	Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "org.gtkmm.ep");

	MainWindow window;

	//Shows the window and returns when it is closed.
	return app->run(window);

	return 0;
}
