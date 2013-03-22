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

		// Load active song from active playlist into a 
		// gstreamer playback, does not start playing yet
		// Triggers E_SONG_CHANGED
		void LoadSong();

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
		const gint64 GetPosition() const { return sound.GetPosition(); }
		const gint64 GetLength() const { return sound.GetLength(); }

		// Select next/previous song from active playlist
		bool NextSong();
		bool PreviousSong();

		// Check for specific status
		bool IsPlaying() { return (sound.GetState() == Gst::STATE_PLAYING); }
		bool IsPaused() { return (sound.GetState() == Gst::STATE_PAUSED); }

		// Note that IsStopped() returns true even when there is no stream
		bool IsStopped() { return (sound.GetState() == Gst::STATE_NULL); }

	private:

		bool _BusWatch(const Glib::RefPtr<Gst::Bus>&, const Glib::RefPtr<Gst::Message>&);

		bool _OnPlaybackTimer();

		void _EndOfStream();

		Sound sound;
		Glib::RefPtr<Gst::Bus> backendBus;

		Playlist *activePlaylist;

		// connection to timer that ticks every one second when playback is on
		sigc::connection playTimer;

		// last loaded uri to playbin
		Glib::ustring _lastUri;
};


#endif /* end PLAYBACK_H */
