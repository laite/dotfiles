/*										
 * widget.h	
 * (c) Markus Klinga
 * 
 */

#ifndef WIDGET_H
#define WIDGET_H

#include <gtkmm.h>

class InfoLabel 
{
	public:

		InfoLabel(std::string s): _label(s) { }

		Gtk::Label& GetWidget() { return _label; }

	private:

		Gtk::Label _label;
};


#endif /* end WIDGET_H */
