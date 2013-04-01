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
	: m_box(Gtk::ORIENTATION_VERTICAL, 5)
	, _label("%a [%l] %n. %t")
{
	set_border_width(5);
	set_default_size(800, 600);

	m_box.set_homogeneous(false);

	// TODO: Create Layout class which would return Gtk::Box
	// aka. the whole layout

	// Widgets
	m_box.pack_start(_label.GetWidget(), false, true);
	m_box.pack_start(_playbackControls.GetWidget(), false, true);
	m_box.pack_end(_playlistView.GetWidget(), true, true);

	this->add(m_box);
	this->show_all();
}

MainWindow::~MainWindow()
{
	Global::Log.Add("Goodbye!");
}

