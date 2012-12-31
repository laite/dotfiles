/*										
 * window.h	
 * (c) Markus Klinga
 * 
 * Handle declaration of main window
 */


#ifndef TIMETRACKER_WINDOW_H
#define TIMETRACKER_WINDOW_H

// basic classes
#include <iostream>
#include <set>
#include <map>

// time - related
#include <ctime>
#include <ratio>
#include <chrono>

// gtkmm
#include <gtkmm.h>

/*
 *  Class References
 */

class DataBase;
class DataItem;
class TreeData;

/*
 *  MainWindow
 */

class MainWindow : public Gtk::Window
{
	public:
		
		/*
		 *  Constructors and Destructors
		 */
		
		MainWindow(DataBase *d);
		virtual ~MainWindow();

	protected:
		
		/*
		 *  Methods
		 */

		void _UpdateStatistics(DataItem&);
		void _AddKeyValueToTextView(const std::string, std::string);
		std::string _GetTimePointTextWithDaysAgo(std::chrono::steady_clock::time_point&);
		
		/*
		 *  Signal Handlers
		 */
		
		void _OnButtonNew();
		void _OnButtonRemove();
		void _OnButtonStart();
		void _OnButtonStop();
		void _OnButtonQuit();

		void _TreeViewSelectionChanged();

		/*
		 *  Widgets
		 *
		 *  Layout
		 */
		
		Gtk::Box _mainVBox;
		Gtk::Box _contentVBox;
		Gtk::VPaned _contentVPaned;
		
		/*
		 *  TreeView
		 */
		
		Gtk::ScrolledWindow _treeViewScrollWindow;
		Gtk::TreeView _treeView;
		TreeData *_treeData;
		
		/*
		 *  Statistics
		 */
		
		Gtk::ScrolledWindow _textViewScrollWindow;
		Gtk::TextView _statisticTextView;
		Glib::RefPtr<Gtk::TextBuffer> _statisticTextBuffer;
		Glib::RefPtr<Gtk::TextBuffer::Tag> _boldedTextTag;

		/*
		 *  Buttons
		 */

		Gtk::ButtonBox _buttonBox;
		Gtk::Button _buttonQuit;
		Gtk::Button _buttonNew;
		Gtk::Button _buttonRemove;
		Gtk::Button _buttonStart;
		Gtk::Button _buttonStop;

		/*
		 *  Other members
		 */

		DataBase *_db;
		DataItem *_activeDataItem;
		bool _isTracking;
		std::chrono::system_clock::time_point _timerBeginPoint;
};

#endif // TIMETRACKER_WINDOW_H
