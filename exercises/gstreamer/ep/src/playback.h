/*										
 * playback.h	
 * (c) Markus Klinga
 * 
 */

#ifndef PLAYBACK_H
#define PLAYBACK_H

#include "backend.h"
#include "playlist.h"

class Playback 
{
	public:

		Playback();
		~Playback();

		void Init();

		void SetActivePlaylist(Playlist *p) { activePlaylist = p; }

		void StartPlayback();
		void StopPlayback();

		// this switches states between PAUSED and PLAYING
		// if current state is neither, function does nothing
		void PausePlayback();

		const Song *GetCurrentSong() const;

		const gint64 GetPosition() const { return sound.GetPosition(); }
		const gint64 GetLength() const { return sound.GetLength(); }

		bool NextSong();
		bool PreviousSong();

		const bool IsPlaying() const { return _playing; }

	private:

		bool _BusWatch(const Glib::RefPtr<Gst::Bus>&, const Glib::RefPtr<Gst::Message>&);

		bool _OnPlaybackTimer();

		void _EndOfStream();

		Sound sound;
		Glib::RefPtr<Gst::Bus> backendBus;

		Playlist *activePlaylist;

		// _playing is true also when state is paused
		bool _playing;

		// connection to timer that ticks every one second when playback is on
		sigc::connection playTimer;
};


#endif /* end PLAYBACK_H */
