/*										
 * window.cpp	
 * (c) Markus Klinga
 * 
 */

#include "window.h"
#include "global.h"
#include "engine.h"
#include "playback.h"

MainWindow::MainWindow()
	: m_box(Gtk::ORIENTATION_VERTICAL)
	, m_button("Play/Stop")
	, m_nextSong("Next Song")
	, m_loadButton("Load Folder")
	, m_label("Click to play!")
	, playback(NULL)
{
	set_border_width(10);

	m_button.signal_clicked().connect(sigc::mem_fun(*this,
				&MainWindow::on_button_clicked));

	m_nextSong.signal_clicked().connect(sigc::mem_fun(*this,
				&MainWindow::on_nextSong_clicked));

	m_loadButton.signal_clicked().connect(sigc::mem_fun(*this,
				&MainWindow::on_loadButton_clicked));

	// Widgets
	m_box.pack_start(m_label, true, true);
	m_box.pack_start(m_button, true, true);
	m_box.pack_start(m_nextSong, true, true);
	m_box.pack_start(m_loadButton, true, true);
	this->add(m_box);

	this->show_all();

	playback = Global::player.GetPlayback();
	playback->Init();
}

MainWindow::~MainWindow()
{
	Global::Log.Add("Goodbye!");
}

bool MainWindow::on_timer()
{
	if (playback->IsPlaying())
	{
		Glib::ustring query = playback->GetCurrentSong()->Query("Playing %t by %a");
		gint64 cur = playback->GetPosition();
		gint64 total = playback->GetLength();
		m_label.set_text(query + " " + std::to_string(static_cast<int>(round(cur/1000000000.0))) + "/" + std::to_string(static_cast<int>(round(total/1000000000.0))));
	}
	else
	{
		m_label.set_text("Stopped.");
	}
	return true;
}

void MainWindow::on_button_clicked()
{
	if (playback->IsPlaying())
	{
		if (labelTimer)
		{
			m_label.set_text("Stopped");
			labelTimer.disconnect();
		}
		playback->StopPlayback();
	}
	else
	{
		playback->StartPlayback();
		if (!labelTimer)
			labelTimer = Glib::signal_timeout().connect(sigc::mem_fun(*this, &MainWindow::on_timer), 1000);
	}
}

void MainWindow::on_nextSong_clicked()
{
	if (playback->IsPlaying())
		playback->StopPlayback();

	playback->NextSong();
	playback->StartPlayback();
}

void MainWindow::on_loadButton_clicked()
{
	// create FileChooserDialog and read its result to member variable _folderName
	Gtk::FileChooserDialog dialog("Please choose a folder", Gtk::FILE_CHOOSER_ACTION_SELECT_FOLDER);
	dialog.set_transient_for(*this);

	// add response buttons
	dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
	dialog.add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_OK);

	int result = dialog.run();

	switch (result)
	{
		case (Gtk::RESPONSE_OK):
		{
			std::string folderName = dialog.get_filename();
			Global::Log.Add("Loading folder " + folderName);
			Global::player.GetLibrary()->LoadFolder(folderName);
			Global::Log.Add("Sending query to current playlist");
			Global::player.GetCurrentPlaylist()->AddQuery("*");
			break;
		}
		default:
		{
			Global::Log.Add("Cancelling whole deal.");
			break;
		}
		
	}
}

