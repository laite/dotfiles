/*										
 * window.h	
 * (c) Markus Klinga
 * 
 */

#ifndef WINDOW_H
#define WINDOW_H

#include <gtkmm.h>
#include <gstreamermm.h>
#include <iostream>
#include <string>

#include "widget.h"

class Playback;

class MainWindow : public Gtk::Window
{
	public:

		MainWindow();
		virtual ~MainWindow();

	protected:

		//Member widgets:
		Gtk::VBox m_box;
		PlaybackControls _playbackControls;
		InfoLabel _label;

};

#endif /* end WINDOW_H */
