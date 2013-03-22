/*										
 * playback.cpp	
 * (c) Markus Klinga
 * 
 */

#include "playback.h"
#include "global.h"
#include "engine.h"

Playback::Playback()
	: activePlaylist(NULL)
	, _lastUri("")
{

}

Playback::~Playback()
{
	if (!IsStopped())
	{
		sound.StopPlaying();
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

void Playback::LoadSong()
{
	if (!IsStopped())
		StopPlayback();

	Glib::ustring uri = activePlaylist->GetCurrentSong()->GetUri();
	_lastUri = uri;
	sound.LoadSong(uri);
	Global::Log.Add("Loaded song: " + _lastUri);
}

void Playback::StartPlayback()
{
	if (activePlaylist->GetCurrentSong()->GetUri() != _lastUri)
		LoadSong();
	else if (!IsStopped())
		StopPlayback();

	sound.StartPlaying();

	if (!playTimer)
		playTimer = Glib::signal_timeout().connect(sigc::mem_fun(*this, &Playback::_OnPlaybackTimer), 1000);

	Global::player.TriggerEvent(Global::EVENT::E_PLAYBACK_STATUS_CHANGED);
}

void Playback::StopPlayback()
{
	if (IsStopped())
		return;

	sound.StopPlaying();
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
			sound.StartPlaying();
			Global::player.TriggerEvent(Global::EVENT::E_PLAYBACK_STATUS_CHANGED);
			break;
		default:
			break;
	}
}

bool Playback::NextSong()
{
	bool hasNext = activePlaylist->NextSong();

	if (hasNext)
		LoadSong();

	return hasNext;
}

bool Playback::PreviousSong()
{
	bool hasPrevious = activePlaylist->PreviousSong();

	if (hasPrevious)
		LoadSong();

	return hasPrevious;
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
	if (IsPlaying())
		Global::player.TriggerEvent(Global::EVENT::E_PLAYBACK_SECOND);

	return true;
}

