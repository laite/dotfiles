/*										
 * backend.cpp	
 * (c) Markus Klinga
 * 
 */

#include "backend.h"

Gst::Format Sound::GST_FORMAT = Gst::FORMAT_TIME;

Sound::Sound()
{
	m_playbin = Gst::ElementFactory::create_element("playbin2", "play");
	m_bus = m_playbin->get_bus();

	guint bus_result = m_bus->add_watch(sigc::mem_fun(*this,
								&Sound::bus_watch));

	std::cout << "bus_result: " << bus_result << std::endl;
}

Sound::~Sound()
{
	StopPlaying();
}

bool Sound::bus_watch(const Glib::RefPtr<Gst::Bus>& bus, const Glib::RefPtr<Gst::Message>& message)
{
	switch (message->get_message_type())
	{
		case Gst::MESSAGE_EOS:
			{
				std::cout << "End of stream reached." << std::endl;
				StopPlaying();
				break;
			}
		case Gst::MESSAGE_ERROR:
			{
				std::cout << "ERROR in stream!" << std::endl;
				StopPlaying();
				break;
			}
		default:
			break;
	}
	return true; 
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

	std::cout << "Starting playback." << std::endl;
	m_playbin->set_property("uri", uri);
	m_playbin->set_property("volume", 0.05);
	m_playbin->set_state(Gst::STATE_PLAYING);

	double vol; 
	m_playbin->get_property("volume", vol);
	std::cout << "vol: " << vol << std::endl;
}

void Sound::StopPlaying()
{
	std::cout << "Stopping playback." << std::endl;
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
