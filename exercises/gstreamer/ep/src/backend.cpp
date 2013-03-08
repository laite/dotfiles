/*										
 * backend.cpp	
 * (c) Markus Klinga
 * 
 */

#include "backend.h"
#include "global.h"

Gst::Format Sound::GST_FORMAT = Gst::FORMAT_TIME;

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

const gint64 Sound::GetPosition() const
{
	gint64 position;
	m_playbin->query_position(Sound::GST_FORMAT, position);

	return position;
}

const gint64 Sound::GetLength() const
{
	gint64 length;
	m_playbin->query_duration(Sound::GST_FORMAT, length);

	return length;
}
