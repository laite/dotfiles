/*										
 * playback.cpp	
 * (c) Markus Klinga
 * 
 */

#include "playback.h"

Playback::Playback(Library *l)
	: library(l)
	, _playing(false)
{
	// get bus watch from backend
	backendBus= sound.GetBus();
	backendBus->add_watch(sigc::mem_fun(*this, &Playback::BusWatch));
}

void Playback::StartPlayback()
{
	Glib::ustring song = library->GetCurrentSong();
	sound.StartPlaying(song);
	_playing = true;
}

void Playback::StopPlayback()
{
	if (_playing)
	{
		sound.StopPlaying();
		_playing = false;
	}

}

void Playback::NextSong()
{
	library->NextSong();
}

bool Playback::BusWatch(const Glib::RefPtr<Gst::Bus>& bus, const Glib::RefPtr<Gst::Message>& message)
{
	switch (message->get_message_type())
	{
		case Gst::MESSAGE_EOS:
			{
				std::cout << "End of stream reached." << std::endl;
				StopPlayback();
				break;
			}
		case Gst::MESSAGE_ERROR:
			{
				std::cout << "ERROR in stream!" << std::endl;
				StopPlayback();
				break;
			}
		default:
			break;
	}
	return true; 
}

