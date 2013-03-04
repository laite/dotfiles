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

		Sound();
		~Sound();

		void StartPlaying(Glib::ustring uri);
		void StopPlaying();

		const gint64 GetPosition() const;
		const gint64 GetLength() const;

		static Gst::Format GST_FORMAT;

		// TODO: move bus to Playback
		bool bus_watch(const Glib::RefPtr<Gst::Bus>& bus, const Glib::RefPtr<Gst::Message>& message);

	private:

		Glib::RefPtr<Gst::Element> m_playbin;
		Glib::RefPtr<Gst::Bus> m_bus;
};

#endif /* end BACKEND_H */
