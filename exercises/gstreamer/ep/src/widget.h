/*										
 * widget.h	
 * (c) Markus Klinga
 * 
 */

#ifndef WIDGET_H
#define WIDGET_H

#include <boost/signal.hpp>
#include <gtkmm.h>
#include <string>
#include <map>

#include "song.h"
#include "playback.h"
#include "global.h"

class BaseWidget 
{
	public:

		BaseWidget();
		~BaseWidget();

		virtual Gtk::Widget& GetWidget() = 0;

	protected:

		typedef boost::signal<void ()>::slot_function_type cb_type;
		void AddEventHook(Global::EVENT e, cb_type cb);

		std::map<Global::EVENT, boost::signals::connection> _hooks;
};

class InfoLabel : public BaseWidget
{
	public:

		InfoLabel(std::string);
		~InfoLabel();

		Gtk::Label& GetWidget() { return _label; }

		// this function puts text 'as is' to label
		void SetText(std::string s) { _label.set_text(s); }

		// this function uses songpointer to find info about it
		// by default, widget shows information about current song
		void SetInfoText(std::string = "", const Song* = NULL);

	private:

		// format for label
		std::string _format;

		// actual label
		Gtk::Label _label;

		// playback reference
		Playback *playback;

		// keep label up
		void _UpdateText();
};


/*
 *  Playback Buttons
 */

class PlaybackButton : public BaseWidget
{
	public:

		PlaybackButton();

		Gtk::Button& GetWidget() { return _button; }

		virtual void Press() = 0;

	protected:

		Gtk::Button _button;

		Playback *playback;
};

class PlayPauseButton : public PlaybackButton 
{
	public:

		PlayPauseButton();
		void Press();
};


#endif /* end WIDGET_H */
