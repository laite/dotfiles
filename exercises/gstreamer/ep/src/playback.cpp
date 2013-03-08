/*										
 * playback.cpp	
 * (c) Markus Klinga
 * 
 */

#include "playback.h"

Playback::Playback()
	: _playing(false)
	, activePlaylist(NULL)
{

}

Playback::~Playback()
{
	StopPlayback();
}

void Playback::Init()
{
	sound.CreatePlaybin();
	// get bus watch from backend
	backendBus = sound.GetBus();
	backendBus->add_watch(sigc::mem_fun(*this, &Playback::BusWatch));
}

void Playback::StartPlayback()
{
	if (_playing)
		StopPlayback();

	Glib::ustring uri = activePlaylist->GetCurrentSong()->GetUri();
	sound.StartPlaying(uri);
	_playing = true;
}

void Playback::StopPlayback()
{
	if (!_playing)
		return;

	sound.StopPlaying();
	_playing = false;
}

bool Playback::NextSong()
{
	return activePlaylist->NextSong();
}

void Playback::EndOfStream()
{
	StopPlayback();
	if (NextSong())
		StartPlayback();
}

bool Playback::BusWatch(const Glib::RefPtr<Gst::Bus>& bus, const Glib::RefPtr<Gst::Message>& message)
{
	switch (message->get_message_type())
	{
		case Gst::MESSAGE_EOS:
			{
				Global::Log.Add("End of stream reached.");
				EndOfStream();
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
