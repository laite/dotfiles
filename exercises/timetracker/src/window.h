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
		void _AddKeyValueToTextView(const std::string, std::string, const std::string suffix="");
		
		void _StartTracking(unsigned int);
		void _StopTracking();
		void _UpdateStartButtonText(bool continuous);

		bool _UpdateStatusLabel();

		/*
		 *  Signal Handlers
		 */
		
		void _LaunchNew();
		void _LaunchRemove();
		void _LaunchEdit();
		void _LaunchQuit();
		void _LaunchPreferences();

		bool _OnMenuButton(GdkEventButton*);
		void _OnLaunchButton();

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
		 *  Statusline and button
		 */

		Gtk::HBox _buttonRowBox;
		Gtk::ButtonBox _buttonBox;
		Gtk::Button _menuButton;
		Gtk::Button _launchButton;
		Gtk::Image _prefImage;

		Gtk::Label _buttonStatusLabel;
		
		/*
		 *  Menu
		 */

		Glib::RefPtr<Gtk::UIManager> _UIManager;
		Glib::RefPtr<Gtk::ActionGroup> _UIActionGroup;
		Gtk::Menu* _popupMenu;

		/*
		 *  Other members
		 */

		DataBase *_db;
		DataItem *_activeDataItem;
};

#endif // TIMETRACKER_WINDOW_H
