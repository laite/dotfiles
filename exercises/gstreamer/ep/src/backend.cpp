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
}

Glib::RefPtr<Gst::Bus> Sound::GetBus() const
{
	return m_playbin->get_bus();
}

void Sound::StartPlaying(Glib::ustring uri)
{
	if (uri == "")
	{
		std::cerr << "No song available from the library!" << std::endl;
		return;
	}
	else
	{
		uri = "file://" + uri;
	}

	Global::Log.Add("Starting playback.");
	m_playbin->set_property("uri", uri);
	m_playbin->set_property("volume", 0.05);
	m_playbin->set_state(Gst::STATE_PLAYING);

	double vol; 
	m_playbin->get_property("volume", vol);
	Global::Log.Add("vol: " + std::to_string(vol));
}

void Sound::StopPlaying()
{
	Global::Log.Add("Stopping playback.");
	m_playbin->set_state(Gst::STATE_NULL);
}

void Sound::ResumePlaying()
{
	Global::Log.Add("Resuming playback.");
	m_playbin->set_state(Gst::STATE_PLAYING);
}

void Sound::PausePlaying()
{
	Global::Log.Add("Pausing playback.");
	m_playbin->set_state(Gst::STATE_PAUSED);
}

Gst::State Sound::GetState() const
{
	Gst::State state, pending;
	m_playbin->get_state(state, pending, Gst::CLOCK_TIME_NONE);

	return state;
}

const gint64 Sound::GetPosition() const
{
	gint64 position;
	Gst::Format gst_format = Gst::FORMAT_TIME;

	m_playbin->query_position(gst_format, position);

	return position;
}

const gint64 Sound::GetLength() const
{
	gint64 length;
	Gst::Format gst_format = Gst::FORMAT_TIME;
	m_playbin->query_duration(gst_format, length);

	return length;
}
