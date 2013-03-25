#include <gtkmm.h>
#include <gstreamermm.h>
#include <iostream>
#include <string>

#include "backend.h"
#include "window.h"
#include "global.h"
#include "engine.h"
#include "config.h"

bool Global::debugMode = true;
LogClass Global::Log;
Engine Global::player;
Options Global::options;

int main(int argc, char* argv[]) 
{
	Gst::init(); 
	Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "org.gtkmm.ep");

	Global::player.LoadConfig();
	Global::player.GetPlayback()->Init();

	MainWindow window;

	//Shows the window and returns when it is closed.
	return app->run(window);

	Global::player.SaveConfig();

	return 0;
}
