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
	, m_loadButton("Load Folder")
	, _label("%a - %t - %p")
	, playback(NULL)
{
	set_border_width(10);

	m_loadButton.signal_clicked().connect(sigc::mem_fun(*this,
				&MainWindow::on_loadButton_clicked));

	// Widgets
	m_box.pack_start(_label.GetWidget(), true, true);
	m_box.pack_start(_playbackControls.GetWidget(), true, true);
	m_box.pack_start(m_loadButton, true, true);
	this->add(m_box);

	playback = Global::player.GetPlayback();
	playback->Init();

	this->show_all();
}

MainWindow::~MainWindow()
{
	Global::Log.Add("Goodbye!");
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

