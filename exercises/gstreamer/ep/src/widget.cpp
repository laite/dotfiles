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
#include "library.h"


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
 *  Playlist view
 */

PlaylistViewerColumns::PlaylistViewerColumns()
{
	add(columnTrack);
	add(columnArtist);
	add(columnAlbum);
	add(columnTitle);
}

PlaylistViewer::PlaylistViewer()
{
	_Init();
}

PlaylistViewer::PlaylistViewer(PlaylistViewer::PLAYLIST_TYPE plType, Playlist *staticList)
	: _playlistType(plType)
{
	if (_playlistType == PLAYLIST_TYPE::PL_STATIC_LIST)
	{
		if (staticList != NULL)
			_playlist = staticList;
		else
		{
			// If we are not given explicit playlist, we switch to active!
			_playlistType == PLAYLIST_TYPE::PL_ACTIVE_LIST;
			Global::Log.Add("WARNING: Could not create static playlist viewer, *staticList was NULL pointer! (switched to active list instead)", false);
		}
	}

	_Init();
}

void PlaylistViewer::_Init()
{
	_scrollBox.add(_treeView);
	_scrollBox.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC); //Only show the scrollbars when they are necessary:

	_treeModel = Gtk::ListStore::create(_columns);
	_treeView.set_model(_treeModel);

	_treeView.append_column("Artist", _columns.columnArtist);
	_treeView.append_column("Album", _columns.columnAlbum);
	_treeView.append_column("Track", _columns.columnTrack);
	_treeView.append_column("Title", _columns.columnTitle);

	// make all columns reorderable and resizable
	std::vector<Gtk::TreeView::Column*> allColumns = _treeView.get_columns();
	for (std::vector<Gtk::TreeView::Column*>::iterator columnIter = allColumns.begin();
			columnIter != allColumns.end(); ++columnIter)
	{
		(*columnIter)->set_reorderable();
		(*columnIter)->set_resizable();
	}

	// Hook to playlist_change so we always show correct items here
	AddEventHook(Global::EVENT::E_PLAYLIST_CHANGED, boost::bind(&PlaylistViewer::_UpdateContents, this));

	// initialize contents
	_UpdateContents();
}

void PlaylistViewer::_UpdateContents()
{
	typedef std::vector<unsigned int> plType;

	if (_playlistType != PLAYLIST_TYPE::PL_STATIC_LIST)
		_playlist = Global::player.GetCurrentPlaylist();

	Library *libraryPointer = Global::player.GetLibrary();

	_treeModel->clear();

	if (!_playlist)
		return;

	plType playlistIDs = _playlist->GetAllSongIDs();
	for (plType::iterator plIter = playlistIDs.begin(); plIter != playlistIDs.end(); ++plIter)
	{
		Gtk::TreeModel::iterator iter = _treeModel->append();
		Gtk::TreeModel::Row row = (*iter);

		row[_columns.columnTrack] = libraryPointer->GetSong(*plIter)->GetTrack();
		row[_columns.columnTitle] = libraryPointer->GetSong(*plIter)->GetTitle();
		row[_columns.columnArtist] = libraryPointer->GetSong(*plIter)->GetArtist();
		row[_columns.columnAlbum] = libraryPointer->GetSong(*plIter)->GetAlbum();
	}
}
