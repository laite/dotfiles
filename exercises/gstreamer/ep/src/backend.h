#ifndef BACKEND_H
#define BACKEND_H

#include <gtkmm.h>
#include <gstreamermm.h>
#include <iostream>
#include <string>

#include "library.h"

class Sound
{
	public:

		Sound(Library *l);
		~Sound();

		void start_playing();
		void stop_playing();

		gint64 get_position();
		gint64 get_length();
		bool is_playing() const { return _playback_on; }

		static Gst::Format GST_FORMAT;

		bool bus_watch(const Glib::RefPtr<Gst::Bus>& bus, const Glib::RefPtr<Gst::Message>& message);
	private:

		Glib::RefPtr<Gst::Element> m_playbin;
		Glib::RefPtr<Gst::Bus> m_bus;

		Library *_library;

		bool _playback_on;
};

#endif /* end BACKEND_H */
