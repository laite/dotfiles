/*										
 * backend.cpp	
 * (c) Markus Klinga
 * 
 */

#include "backend.h"
#include "global.h"

Sound::Sound()
{
	
}

Sound::~Sound()
{
	//StopPlaying();
}

void Sound::CreatePlaybin()
{
	m_playbin = Gst::ElementFactory::create_element("playbin2", "play");
	// TODO: proper method for volume (widget, config)
	m_playbin->set_property("volume", 0.05);
}

Glib::RefPtr<Gst::Bus> Sound::GetBus() const
{
	return m_playbin->get_bus();
}

void Sound::LoadSong(Glib::ustring uri)
{
	if (uri == "")
	{
		std::cerr << "No song available from the library!" << std::endl;
		return;
	}
	else
		uri = "file://" + uri;

	m_playbin->set_property("uri", uri);
}

void Sound::StartPlaying()
{
	Global::Log.Add("Starting playback.");
	m_playbin->set_state(Gst::STATE_PLAYING);
}

void Sound::StopPlaying()
{
	Global::Log.Add("Stopping playback.");
	m_playbin->set_state(Gst::STATE_NULL);
}

void Sound::PausePlaying()
{
	Global::Log.Add("Pausing playback.");
	m_playbin->set_state(Gst::STATE_PAUSED);
}

// TODO: take care of pending states (Gst::STATE_VOID_PENDING)
Gst::State Sound::GetState() const
{
	Gst::State state, pending;
	m_playbin->get_state(state, pending, Gst::CLOCK_TIME_NONE);

	return state;
}

const gint64 Sound::GetPosition() const
{
	if (GetState() == Gst::STATE_NULL)
		return 0;

	gint64 position;
	Gst::Format gst_format = Gst::FORMAT_TIME;

	m_playbin->query_position(gst_format, position);

	return position;
}

const gint64 Sound::GetLength() const
{
	// TODO: there should be length even when not playing
	if (GetState() == Gst::STATE_NULL)
		return 0;

	gint64 length;
	Gst::Format gst_format = Gst::FORMAT_TIME;
	m_playbin->query_duration(gst_format, length);

	return length;
}
