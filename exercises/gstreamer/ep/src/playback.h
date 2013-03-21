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

		// Create playbin and obtain bus
		void Init();

		// Starts playing the active song of an active playlist
		// Creates playback timer if necessary
		// Triggers E_PLAYBACK_STATUS_CHANGED
		void StartPlayback();

		// Stops playback, disconnects playback timer
		// Triggers E_PLAYBACK_STATUS_CHANGED
		void StopPlayback();

		// Switches playback states between PAUSED and PLAYING
		// if current state is neither, function does nothing
		void PausePlayback();

		// Sets active playlist
		// TODO: trigger
		void SetActivePlaylist(Playlist *p) { activePlaylist = p; }

		// Returns pointer to active song on an active playlist
		const Song *GetCurrentSong() const;

		// Some Getters
		Gst::State GetState() const { return sound.GetState(); }
		const gint64 GetPosition() const { return sound.GetPosition(); }
		const gint64 GetLength() const { return sound.GetLength(); }

		// Select next/previous song from active playlist
		bool NextSong() { return activePlaylist->NextSong(); }
		bool PreviousSong() { return activePlaylist->PreviousSong(); }

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
