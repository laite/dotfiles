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

		//Signal handlers:
		void on_button_clicked();
		void on_nextSong_clicked();
		bool on_timer();
		void on_loadButton_clicked();

		//Member widgets:
		Gtk::VBox m_box;
		Gtk::Button m_button;
		Gtk::Button m_loadButton;
		Gtk::Button m_nextSong;
		InfoLabel _label;

	private:

		Playback *playback;

		sigc::connection labelTimer;
};

#endif /* end WINDOW_H */
