#include <gtkmm.h>
#include <gstreamermm.h>
#include <iostream>
#include <string>

class Sound
{
	public:
		Sound();

		void start_playing(const Glib::ustring &uri);
		void stop_playing();

		gint64 get_position();
		gint64 get_length();
		bool is_playing() const { return _playback_on; }

		static Gst::Format GST_FORMAT;

		bool bus_watch(const Glib::RefPtr<Gst::Bus>& bus, const Glib::RefPtr<Gst::Message>& message);
	private:

		Glib::RefPtr<Gst::Element> m_playbin;
		Glib::RefPtr<Gst::Bus> m_bus;

		bool _playback_on;
};

Gst::Format Sound::GST_FORMAT = Gst::FORMAT_TIME;

Sound::Sound()
	: _playback_on(false)
{
	m_playbin = Gst::ElementFactory::create_element("playbin2", "play");
	m_bus = m_playbin->get_bus();

	guint bus_result = m_bus->add_watch(sigc::mem_fun(*this,
								&Sound::bus_watch));

	std::cout << "bus_result: " << bus_result << std::endl;
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

void Sound::start_playing(const Glib::ustring &uri)
{
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

class HelloWorld : public Gtk::Window
{

	public:
		HelloWorld();
		virtual ~HelloWorld();

	protected:
		//Signal handlers:
		void on_button_clicked();
		bool on_timer();
		void on_loadButton_clicked();

		//Member widgets:
		Gtk::VBox m_box;
		Gtk::Button m_button;
		Gtk::Button m_loadButton;
		Gtk::Label m_label;
		Sound sound;

	private:

		Glib::ustring _songName;
};

HelloWorld::HelloWorld()
	: m_box(Gtk::ORIENTATION_VERTICAL)
	, m_button("Play/Stop")
	, m_loadButton("Load file")
	, m_label("Click to play!")
	, _songName("file:///home/laite/workspace/c++/gstreamer/test.mp3")
{
	set_border_width(10);

	m_button.signal_clicked().connect(sigc::mem_fun(*this,
				&HelloWorld::on_button_clicked));

	m_loadButton.signal_clicked().connect(sigc::mem_fun(*this,
				&HelloWorld::on_loadButton_clicked));

	// Widgets
	m_box.pack_start(m_label, true, true);
	m_box.pack_start(m_button, true, true);
	m_box.pack_start(m_loadButton, true, true);
	this->add(m_box);

	this->show_all();
}

HelloWorld::~HelloWorld()
{
	std::cout << "Goodbye!" << std::endl;
}

bool HelloWorld::on_timer()
{
	if (sound.is_playing())
	{
		gint64 cur = sound.get_position();
		gint64 total = sound.get_length();
		m_label.set_text("Playing: " + std::to_string(static_cast<int>(round(cur/1000000000.0))) + "/" + std::to_string(static_cast<int>(round(total/1000000000.0))));
	}
	else
	{
		m_label.set_text("Stopped.");
	}
	return sound.is_playing();
}

void HelloWorld::on_button_clicked()
{
	if (sound.is_playing())
		sound.stop_playing();
	else
	{
		sound.start_playing(_songName);
		Glib::signal_timeout().connect(sigc::mem_fun(*this, &HelloWorld::on_timer), 1000);
	}
}

void HelloWorld::on_loadButton_clicked()
{
	// create FileChooserDialog and read its result to member variable _songName
	Gtk::FileChooserDialog dialog("Please choose a song", Gtk::FILE_CHOOSER_ACTION_OPEN);
	dialog.set_transient_for(*this);

	// add response buttons
	dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
	dialog.add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_OK);

	// add file type filters
	Glib::RefPtr<Gtk::FileFilter> filter_mp3 = Gtk::FileFilter::create();
	filter_mp3->set_name("Mpeg audio");
	filter_mp3->add_mime_type("audio/mpeg");
	dialog.add_filter(filter_mp3);

	Glib::RefPtr<Gtk::FileFilter> filter_all = Gtk::FileFilter::create();
	filter_all->set_name("All files");
	filter_all->add_pattern("*");
	dialog.add_filter(filter_all);

	int result = dialog.run();

	switch (result)
	{
		case (Gtk::RESPONSE_OK):
		{
			std::string fileName = dialog.get_filename();
			std::cout << "Loading file " << fileName << std::endl;
			_songName = "file://" + fileName;
			break;
		}
		default:
		{
			std::cout << "Cancelling whole deal." << std::endl;
			break;
		}
		
	}
}

int main(int argc, char* argv[]) 
{

	Gst::init(); 

	Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "org.gtkmm.example");

	HelloWorld helloworld;

	//Shows the window and returns when it is closed.
	return app->run(helloworld);

	return 0;
}
