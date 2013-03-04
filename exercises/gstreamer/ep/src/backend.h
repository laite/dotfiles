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

		Glib::RefPtr<Gst::Bus> GetBus() const;

		static Gst::Format GST_FORMAT;

	private:

		Glib::RefPtr<Gst::Element> m_playbin;
};

#endif /* end BACKEND_H */
