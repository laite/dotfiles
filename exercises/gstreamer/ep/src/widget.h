/*										
 * widget.h	
 * (c) Markus Klinga
 * 
 */

#ifndef WIDGET_H
#define WIDGET_H

#include <boost/signal.hpp>
#include <gtkmm.h>
#include <string>
#include <map>

#include "song.h"
#include "playback.h"
#include "global.h"

class Playlist;
class Library;

class BaseWidget 
{
	public:

		BaseWidget();
		~BaseWidget();

		virtual Gtk::Widget& GetWidget() = 0;

	protected:

		typedef boost::signal<void ()>::slot_function_type cb_type;
		void AddEventHook(Global::EVENT e, cb_type cb);

		std::map<Global::EVENT, boost::signals::connection> _hooks;
};

class InfoLabel : public BaseWidget
{
	public:

		explicit InfoLabel(std::string);
		~InfoLabel();

		Gtk::Label& GetWidget() { return _label; }

		// this function puts text 'as is' to label
		void SetText(std::string s) { _label.set_text(s); }

		// this function uses songpointer to find info about it
		// by default, widget shows information about current song
		void SetInfoText(std::string = "", const Song* = NULL);

	private:

		// format for label
		std::string _format;

		// actual label
		Gtk::Label _label;

		// playback reference
		Playback *playback;

		// keep label up
		void _UpdateText();
};


/*
 *  Playback Buttons
 */

class PlaybackButton : public BaseWidget
{
	public:

		PlaybackButton();

		Gtk::Button& GetWidget() { return _button; }

		virtual void Press() = 0;

	protected:

		Gtk::Button _button;
		Gtk::Image _image;

		// TODO: could/should this be static?
		Playback *playback;
};

class PlayPauseButton : public PlaybackButton
{
	public:

		PlayPauseButton();
		void Press();

	private:

		void _UpdateIcon();
};

class PlayButton : public PlaybackButton
{
	public:

		PlayButton();
		void Press();
};

class PauseButton : public PlaybackButton
{
	public:

		PauseButton();
		void Press();
};

class StopButton : public PlaybackButton
{
	public:

		StopButton();
		void Press();
};

class NextButton : public PlaybackButton
{
	public:

		NextButton();
		void Press();
};

class PreviousButton : public PlaybackButton
{
	public:

		PreviousButton();
		void Press();
};


/*
 *  Playback Controls
 */

class PlaybackControls : public BaseWidget
{
	public:

		explicit PlaybackControls(Gtk::Orientation orientation = Gtk::ORIENTATION_HORIZONTAL);
		Gtk::Box& GetWidget() { return _widget; }

	private:

		Gtk::Box _widget;

		PreviousButton _prev;
		NextButton _next;
		PlayPauseButton _playpause;
		StopButton _stop;
};


/*
 *  Playlist View
 */

class PlaylistViewerColumns : public Gtk::TreeModel::ColumnRecord
{
	friend class PlaylistViewer;

	private:

		PlaylistViewerColumns();

		Gtk::TreeModelColumn<unsigned int> columnRowNumber;
		Gtk::TreeModelColumn<unsigned int> columnSongID;
		Gtk::TreeModelColumn<unsigned int> columnTrack;
		Gtk::TreeModelColumn<Glib::ustring> columnArtist;
		Gtk::TreeModelColumn<Glib::ustring> columnAlbum;
		Gtk::TreeModelColumn<Glib::ustring> columnTitle;
};

class PlaylistViewer : public BaseWidget
{
	public:

		// TODO: add more options (like 'currently playing artist')
		enum PLAYLIST_TYPE { PL_ACTIVE_LIST, PL_STATIC_LIST };


		/*
		 *  Constructors
		 */


		// if constructor gets single playlist reference, we set playlist type to static
		PlaylistViewer(Playlist *staticList = NULL);


		/*
		 *  Public Methods
		 */


		Gtk::Widget& GetWidget() { return _scrollBox; }

	private:

		/*
		 *  Private Methods
		 */

		// Initialize treeview, treemodel etc.
		void _Init();
		
		// Redraw all data
		void _UpdateContents();

		// Handle song changing
		void _SongChanged();

		void _SelectionChanged();
		
		std::vector<Gtk::TreeModel::Row> _GetSelectedSongRows();

		/*
		 *  Members
		 */

		PLAYLIST_TYPE _playlistType;

		// reference to playlist showing
		Playlist *_playlist;

		// reference to library
		Library *_library;
		
		// All columns (including hidden ones)
		PlaylistViewerColumns _columns;

		// scrollbox for treeview
		Gtk::ScrolledWindow _scrollBox;

		// actual treeview
		Gtk::TreeView _treeView;
		
		// underlying model and selection
		Glib::RefPtr<Gtk::ListStore> _treeModel;
		Glib::RefPtr<Gtk::TreeSelection> _refTreeSelection;
};

#endif /* end WIDGET_H */
