/*										
 * backend.cpp	
 * (c) Markus Klinga
 * 
 */

#include "backend.h"

Gst::Format Sound::GST_FORMAT = Gst::FORMAT_TIME;

Sound::Sound(Library *l)
	: _playback_on(false)
	, _library(l)
{
	m_playbin = Gst::ElementFactory::create_element("playbin2", "play");
	m_bus = m_playbin->get_bus();

	guint bus_result = m_bus->add_watch(sigc::mem_fun(*this,
								&Sound::bus_watch));

	std::cout << "bus_result: " << bus_result << std::endl;
}

Sound::~Sound()
{
	if (_playback_on)
		stop_playing();
}

bool Sound::bus_watch(const Glib::RefPtr<Gst::Bus>& bus, const Glib::RefPtr<Gst::Message>& message)
{
	switch (message->get_message_type())
	{
		case Gst::MESSAGE_EOS:
			{
				std::cout << "End of stream reached." << std::endl;
				stop_playing();
				break;
			}
		case Gst::MESSAGE_ERROR:
			{
				std::cout << "ERROR in stream!" << std::endl;
				stop_playing();
				break;
			}
		default:
			break;
	}
	return true; 
}

void Sound::start_playing()
{
	Glib::ustring uri = _library->GetCurrentSong();

	if (uri == "")
	{
		std::cerr << "No song available from the library!" << std::endl;
		return;
	}
	else
	{
		uri = "file://" + uri;
	}

	std::cout << "Starting playback." << std::endl;
	m_playbin->set_property("uri", uri);
	m_playbin->set_property("volume", 0.05);
	m_playbin->set_state(Gst::STATE_PLAYING);
	_playback_on = true;

	double vol; 
	m_playbin->get_property("volume", vol);
	std::cout << "vol: " << vol << std::endl;
}

void Sound::stop_playing()
{
	std::cout << "Stopping playback." << std::endl;
	_playback_on = false;
	m_playbin->set_state(Gst::STATE_NULL);
}

gint64 Sound::get_position()
{
	gint64 position;
	m_playbin->query_position(Sound::GST_FORMAT, position);

	return position;
}

gint64 Sound::get_length()
{
	gint64 length;
	m_playbin->query_duration(Sound::GST_FORMAT, length);

	return length;
}
