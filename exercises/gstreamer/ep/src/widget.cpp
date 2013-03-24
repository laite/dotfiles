/*										
 * widget.cpp	
 * (c) Markus Klinga
 * 
 */

#include <boost/bind.hpp>

#include "widget.h"
#include "global.h"
#include "engine.h"
#include "config.h"


/*
 *  BaseWidget
 */


BaseWidget::BaseWidget()
{
	
}

BaseWidget::~BaseWidget()
{
	if (_hooks.size() > 0)
	{
		typedef std::map<Global::EVENT, boost::signals::connection>::iterator hookIter;
		for (hookIter iter = _hooks.begin(); iter != _hooks.end(); ++iter)
			Global::player.Unhook(iter->first, iter->second);
	}
}

void BaseWidget::AddEventHook(Global::EVENT e, BaseWidget::cb_type cb)
{
	// Hook to event
	boost::signals::connection c = Global::player.Hook(e, cb);
	_hooks[e] = c;
}

/*
 *  InfoLabel
 */


InfoLabel::InfoLabel(std::string s)
{
	_format = s;
	playback = Global::player.GetPlayback();

	SetInfoText(s);

	// TODO: only hook to playback_second if it's necessary
	AddEventHook(Global::EVENT::E_PLAYBACK_SECOND, boost::bind(&InfoLabel::_UpdateText, this));

	AddEventHook(Global::EVENT::E_SONG_CHANGED, boost::bind(&InfoLabel::_UpdateText, this));
}

InfoLabel::~InfoLabel()
{

}

void InfoLabel::SetInfoText(std::string format, const Song* song)
{
	// if we're given a format for this function, we'll keep using that from now on
	if (format != "")
		_format = format;

	if (!song)
		song = playback->GetCurrentSong();

	Glib::ustring query(_format);
	
	// GetCurrentSong might also return NULL in which case there is not necessarily
	// a song to get information from
	if (song)
	{
		// TODO: grab all non-song related items from format before sending to ->Query()
		query = song->Query(_format);
		gint64 cur = playback->GetPosition();
		gint64 total = playback->GetLength();
		query += " " + std::to_string(static_cast<int>(round(cur/1000000000.0))) + "/" + std::to_string(static_cast<int>(round(total/1000000000.0)));
	}

	_label.set_text(query);
}

void InfoLabel::_UpdateText()
{
	SetInfoText();
}


/*
 *  Playback Buttons
 */

PlaybackButton::PlaybackButton()
{
	playback = Global::player.GetPlayback();
	_button.signal_clicked().connect( sigc::mem_fun(*this,
				              &PlaybackButton::Press) );
	_button.set_image(_image);
}


/*
 *  PlayPause Button
 */

PlayPauseButton::PlayPauseButton()
{
	_button.set_label((Global::options.GetAppOptions().playbackButtonLabels)? "Play/Pause" : "");
	_image.set(Gtk::Stock::MEDIA_PLAY, Gtk::ICON_SIZE_MENU);

	AddEventHook(Global::EVENT::E_PLAYBACK_STATUS_CHANGED, boost::bind(&PlayPauseButton::_UpdateIcon, this));
}

void PlayPauseButton::Press()
{
	if (playback->IsStopped())
		playback->StartPlayback();
	else
		playback->PausePlayback();
}

void PlayPauseButton::_UpdateIcon()
{
	if (playback->IsPlaying())
		_image.set(Gtk::Stock::MEDIA_PAUSE, Gtk::ICON_SIZE_MENU);
	else
		_image.set(Gtk::Stock::MEDIA_PLAY, Gtk::ICON_SIZE_MENU);
}

/*
 *  Play Button
 */

PlayButton::PlayButton()
{
	_button.set_label((Global::options.GetAppOptions().playbackButtonLabels)? "Play" : "");
	_image.set(Gtk::Stock::MEDIA_PLAY, Gtk::ICON_SIZE_MENU);
}

void PlayButton::Press()
{
	playback->StartPlayback();
}

/*
 *  Stop Button
 */

StopButton::StopButton()
{
	_button.set_label((Global::options.GetAppOptions().playbackButtonLabels)? "Stop" : "");
	_image.set(Gtk::Stock::MEDIA_STOP, Gtk::ICON_SIZE_MENU);
}

void StopButton::Press()
{
	playback->StopPlayback();
}

/*
 *  Pause Button
 */

PauseButton::PauseButton()
{
	_button.set_label((Global::options.GetAppOptions().playbackButtonLabels)? "Pause" : "");
	_image.set(Gtk::Stock::MEDIA_PAUSE, Gtk::ICON_SIZE_MENU);
}

void PauseButton::Press()
{
	playback->PausePlayback();
}

/*
 *  Next Button
 */

NextButton::NextButton()
{
	_button.set_label((Global::options.GetAppOptions().playbackButtonLabels)? "Next" : "");
	_image.set(Gtk::Stock::MEDIA_NEXT, Gtk::ICON_SIZE_MENU);
}

void NextButton::Press()
{
	playback->NextSong();
}

/*
 *  Previous Button
 */

PreviousButton::PreviousButton()
{
	_button.set_label((Global::options.GetAppOptions().playbackButtonLabels)? "Previous" : "");
	_image.set(Gtk::Stock::MEDIA_PREVIOUS, Gtk::ICON_SIZE_MENU);
}

void PreviousButton::Press()
{
	playback->PreviousSong();
}


/*
 *  Playback Controls
 */

PlaybackControls::PlaybackControls(Gtk::Orientation orientation)
	: _widget(orientation)
{
	_widget.pack_start(_prev.GetWidget(), true, true);
	_widget.pack_start(_playpause.GetWidget(), true, true);
	_widget.pack_start(_stop.GetWidget(), true, true);
	_widget.pack_start(_next.GetWidget(), true, true);
}


/*
TODO : add load button sometime
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
			//Global::player.GetLibrary()->LoadFolder(folderName);
			Global::Log.Add("Sending query to current playlist");
			//Global::player.GetCurrentPlaylist()->AddQuery("*");
			break;
		}
		default:
		{
			Global::Log.Add("Cancelling whole deal.");
			break;
		}
		
	}
}

*/
