/*										
 * playback.cpp	
 * (c) Markus Klinga
 * 
 */

#include "playback.h"
#include "global.h"
#include "engine.h"

Playback::Playback()
	: _playing(false)
	, activePlaylist(NULL)
{

}

Playback::~Playback()
{
	if (_playing)
	{
		sound.StopPlaying();
		_playing = false;
		if (playTimer)
			playTimer.disconnect();
	}
}

void Playback::Init()
{
	sound.CreatePlaybin();
	// get bus watch from backend
	backendBus = sound.GetBus();
	backendBus->add_watch(sigc::mem_fun(*this, &Playback::_BusWatch));
}

void Playback::StartPlayback()
{
	if (_playing)
		StopPlayback();

	Glib::ustring uri = activePlaylist->GetCurrentSong()->GetUri();
	sound.StartPlaying(uri);
	_playing = true;

	if (!playTimer)
		playTimer = Glib::signal_timeout().connect(sigc::mem_fun(*this, &Playback::_OnPlaybackTimer), 1000);

	Global::player.TriggerEvent(Global::EVENT::E_PLAYBACK_STATUS_CHANGED);
}

void Playback::StopPlayback()
{
	if (!_playing)
		return;

	sound.StopPlaying();
	_playing = false;
	if (playTimer)
		playTimer.disconnect();

	Global::player.TriggerEvent(Global::EVENT::E_PLAYBACK_STATUS_CHANGED);
}

void Playback::PausePlayback()
{
	Gst::State state = sound.GetState();

	switch (state)
	{
		case Gst::STATE_PLAYING:
			sound.PausePlaying();
			Global::player.TriggerEvent(Global::EVENT::E_PLAYBACK_STATUS_CHANGED);
			break;
		case Gst::STATE_PAUSED:
			sound.ResumePlaying();
			Global::player.TriggerEvent(Global::EVENT::E_PLAYBACK_STATUS_CHANGED);
			break;
		default:
			break;
	}
}

void Playback::_EndOfStream()
{
	StopPlayback();
	if (NextSong())
		StartPlayback();
}

bool Playback::_BusWatch(const Glib::RefPtr<Gst::Bus>& bus, const Glib::RefPtr<Gst::Message>& message)
{
	switch (message->get_message_type())
	{
		case Gst::MESSAGE_EOS:
			{
				Global::Log.Add("End of stream reached.");
				_EndOfStream();
				break;
			}
		case Gst::MESSAGE_ERROR:
			{
				Global::Log.Add("ERROR in stream!");
				StopPlayback();
				break;
			}
		default:
			break;
	}
	return true; 
}

const Song* Playback::GetCurrentSong() const
{
	return activePlaylist->GetCurrentSong();
}

bool Playback::_OnPlaybackTimer()
{
	if (_playing)
		Global::player.TriggerEvent(Global::EVENT::E_PLAYBACK_SECOND);

	return true;
}

