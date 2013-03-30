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
{
	set_border_width(10);

	// TODO: Create Layout class which would return Gtk::Box
	// aka. the whole layout

	// Widgets
	m_box.pack_start(_label.GetWidget(), true, true);
	m_box.pack_start(_playbackControls.GetWidget(), true, true);
	m_box.pack_start(_playlistView.GetWidget(), true, true);

	this->add(m_box);
	this->show_all();
}

MainWindow::~MainWindow()
{
	Global::Log.Add("Goodbye!");
}

