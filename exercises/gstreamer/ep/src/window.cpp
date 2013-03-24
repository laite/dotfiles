/*										
 * window.cpp	
 * (c) Markus Klinga
 * 
 */

#include "window.h"
#include "global.h"
#include "engine.h"
#include "playback.h"

MainWindow::MainWindow()
	: m_box(Gtk::ORIENTATION_VERTICAL)
	, _label("%a - %t - %p")
	, playback(NULL)
{
	set_border_width(10);

	// Widgets
	m_box.pack_start(_label.GetWidget(), true, true);
	m_box.pack_start(_playbackControls.GetWidget(), true, true);
	this->add(m_box);

	playback = Global::player.GetPlayback();

	this->show_all();
}

MainWindow::~MainWindow()
{
	Global::Log.Add("Goodbye!");
}

