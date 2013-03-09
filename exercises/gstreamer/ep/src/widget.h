/*										
 * widget.h	
 * (c) Markus Klinga
 * 
 */

#ifndef WIDGET_H
#define WIDGET_H

#include <gtkmm.h>
#include <string>

#include "song.h"
#include "playback.h"

class InfoLabel 
{
	public:

		InfoLabel(std::string);

		Gtk::Label& GetWidget() { return _label; }

		// this function puts text 'as is' to label
		void SetText(std::string s) { _label.set_text(s); }

		// this function uses songpointer to find info about it
		// by default, widget shows information about current song
		void SetInfoText(std::string, const Song* = NULL);

	private:

		Gtk::Label _label;

		Playback *playback;
};


#endif /* end WIDGET_H */
