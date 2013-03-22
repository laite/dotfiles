#ifndef BACKEND_H
#define BACKEND_H

#include <gtkmm.h>
#include <gstreamermm.h>
#include <iostream>
#include <string>

class Sound
{
	friend class Playback;

	private:

		Sound();
		~Sound();

		// init gstreamer with creating simple playbin2
		void CreatePlaybin();

		// LoadSong takes full path of file as parameter
		// (without file://)
		void LoadSong(Glib::ustring uri);

		// Start playing the loaded song
		void StartPlaying();

		// sets playbin state to Gst::STATE_NULL
		void StopPlaying();

		// set playbin state to Gst::STATE_PAUSED
		void PausePlaying();

		Gst::State GetState() const;
		const gint64 GetPosition() const;
		const gint64 GetLength() const;

		// used to hook onto streams messagebus
		Glib::RefPtr<Gst::Bus> GetBus() const;

		// actual playbin
		Glib::RefPtr<Gst::Element> m_playbin;
};

#endif /* end BACKEND_H */
