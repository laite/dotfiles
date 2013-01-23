/*										
 * window.cpp	
 * (c) Markus Klinga
 * 
 * Definitions of MainWindow
 */

#include <iostream>
#include <chrono>
#include <cstdlib>
#include "log.h"
#include "window.h"
#include "data.h" // need DataBase class implementation
#include "helpers.h"
#include "treedata.h"
#include "dialogs.h"

MainWindow::MainWindow(DataBase *d)
	: _db(d) // main database (pointer)
	, _mainVBox(Gtk::ORIENTATION_VERTICAL)
	, _contentVBox(Gtk::ORIENTATION_VERTICAL)
	, _prefImage("/home/laite/.config/laite/timetracker/timetracker32.png")
	, _buttonStatusLabel("Everything seems to be fine.")
	, _launchButton("Start")
	, _activeDataItem(NULL)
{

	set_title("TimeTracker/laite");
	set_border_width(5);
	set_default_size(Global::Config.GetAppOptions().defaultWindowSize.first, Global::Config.GetAppOptions().defaultWindowSize.second);

	/*
	 *  Containers and widgets
	 *
	 *  Popup menu
	 */

	_UIActionGroup = Gtk::ActionGroup::create();

	_UIActionGroup->add( Gtk::Action::create("ContextMenu", "Context Menu"));
	_UIActionGroup->add( Gtk::Action::create("ContextNew", "New"), sigc::mem_fun(*this, &MainWindow::_OnButtonNew) );
	_UIActionGroup->add( Gtk::Action::create("ContextEdit", "Edit"), sigc::mem_fun(*this, &MainWindow::_OnButtonEdit) );
	_UIActionGroup->add( Gtk::Action::create("ContextRemove", "Remove"), sigc::mem_fun(*this, &MainWindow::_OnButtonRemove) );
	_UIActionGroup->add( Gtk::Action::create("ContextPreferences", "Preferences"), sigc::mem_fun(*this, &MainWindow::_OnButtonPreferences) );
	_UIActionGroup->add( Gtk::Action::create("ContextQuit", "Quit"), sigc::mem_fun(*this, &MainWindow::_OnButtonQuit) );

	_UIManager = Gtk::UIManager::create();
	_UIManager->insert_action_group(_UIActionGroup);
	add_accel_group(_UIManager->get_accel_group());

	Glib::ustring ui_info =
		"<ui>"
		"  <popup name='PopupMenu'>"
		"    <menuitem action='ContextNew'/>"
		"    <menuitem action='ContextEdit'/>"
		"    <menuitem action='ContextRemove'/>"
        "    <separator/>"
		"    <menuitem action='ContextPreferences'/>"
        "    <separator/>"
		"    <menuitem action='ContextQuit'/>"
		"  </popup>"
		"</ui>";

	try {
		_UIManager->add_ui_from_string(ui_info);
	}
	catch(const Glib::Error& ex) {
		Global::Log.Add("ERROR! " + ex.what());
	}

	_popupMenu = dynamic_cast<Gtk::Menu*>(
			_UIManager->get_widget("/PopupMenu")); 
	if(!_popupMenu)
		g_warning("Menu creation failed!");

	/*
	 *  ContentVBox
	 */
	
	_treeViewScrollWindow.add(_treeView);
	_treeViewScrollWindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC); //Only show the scrollbars when they are necessary:

	_textViewScrollWindow.add(_statisticTextView);
	_textViewScrollWindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC); //Only show the scrollbars when they are necessary:

	_contentVPaned.add1(_treeViewScrollWindow);
	_contentVPaned.add2(_textViewScrollWindow);
	_contentVPaned.set_position(Global::Config.GetAppOptions().panedPosition);

	_contentVBox.pack_start(_contentVPaned, true, true);
	
	/*
	 *  Status text
	 */
	
	// create a tag for bolding 'values' in statitems
	_boldedTextTag = Gtk::TextBuffer::Tag::create("bolded_text");
	_boldedTextTag->property_weight() = PANGO_WEIGHT_BOLD;

	// We have to create a 'tagTable' to pass it to buffer
	Glib::RefPtr<Gtk::TextBuffer::TagTable> refTagTable = Gtk::TextBuffer::TagTable::create();
	refTagTable->add(_boldedTextTag);

	_statisticTextBuffer = Gtk::TextBuffer::create(refTagTable);
	_statisticTextView.set_buffer(_statisticTextBuffer);

	_statisticTextView.set_editable(false);
	_statisticTextView.set_wrap_mode(Gtk::WRAP_WORD);

	/*
	 *  Statusline and buttons
	 */

	_menuButton.set_image(_prefImage);
	_buttonStatusLabel.set_alignment(0.5, 0.5);

	_buttonBox.pack_start(_launchButton, Gtk::PACK_SHRINK);

	_buttonRowBox.pack_start(_menuButton, false, false);
	_buttonRowBox.pack_start(_buttonStatusLabel, true, true);
	_buttonRowBox.pack_start(_buttonBox, false, false);

	_buttonBox.set_border_width(5);
	_buttonRowBox.set_border_width(5);
	_buttonBox.set_layout(Gtk::BUTTONBOX_END);

	/*
	 *  MainVBox
	 */

	add(_mainVBox); // the main VBox
	_mainVBox.pack_start(_buttonRowBox, Gtk::PACK_SHRINK);
	_mainVBox.pack_start(_contentVBox);

	/*
	 *  Widget rules
	 */

	_treeData = new TreeData(&_treeView, _db);
	_treeData->InitializeTreeView();
	_treeData->PopulateTreeModel();

	/*
	 *  Add signals
	 */
	_menuButton.signal_button_press_event().connect( sigc::mem_fun(*this, &MainWindow::_OnMenuButton), false);
	_launchButton.signal_clicked().connect( sigc::mem_fun(*this, &MainWindow::_OnLaunchButton), false);

	_treeData->GetRefTreeSelection()->signal_changed().connect(sigc::mem_fun(*this, &MainWindow::_TreeViewSelectionChanged));

	/*
	 *  Select first row by default (if there is one)
	 */
	
	if (_db->GetSize() > 0) {
		Gtk::TreeModel::Children treeChildren = _treeData->GetRefTreeModel()->children();
		_treeData->GetRefTreeSelection()->select(*(treeChildren.begin()));
	}
	else
	{
		_launchButton.set_sensitive(0);
	}
	
	/*
	 *  Release
	 */
	
	show_all_children();

}

MainWindow::~MainWindow()
{
	Global::Config.SetAppOptions().defaultWindowSize.first = this->get_width();
	Global::Config.SetAppOptions().defaultWindowSize.second = this->get_height();
	Global::Config.SetAppOptions().panedPosition = _contentVPaned.get_position();
	Global::Log.Add("Killing MainWindow");
}

void MainWindow::_OnLaunchButton()
{
	if (_activeDataItem) // if we are currently tracking
	{
		_StopTracking();
	}
	else
	{
		int selectedID = _treeData->GetSelectedID();

		// See if there's an ID, and that it exists in _db
		if ((selectedID == 0) || (!_db->IsIn(selectedID))) {
			Global::Log.Add("* ERROR * Can not find item with ID = " + std::to_string(selectedID));
			return;
		}

		_StartTracking(selectedID);
	}
}

void MainWindow::_OnButtonNew()
{
	DataItemDialog dialog;
	DataItem newItem;

	if (dialog.LaunchDialog(&newItem) == Gtk::RESPONSE_OK)
	{
		Global::Log.Add("New Item - dialog gives OK.");
		_db->AddItemToDataBase(newItem);
		_treeData->AddRow(newItem, true);
		_launchButton.set_sensitive(1);
	}
}

void MainWindow::_OnButtonEdit()
{
	DataItemDialog dialog;
	unsigned int currentID = _treeData->GetSelectedID();

	if (dialog.LaunchDialog(&_db->GetItem(currentID)) == Gtk::RESPONSE_OK)
	{
		_db->UpdateItemStats(currentID);
		_treeData->UpdateRow(_treeData->GetRowIterFromID(currentID));
		Global::Log.Add("Edited file successfully.");
	}
}

void MainWindow::_OnButtonRemove()
{
	if (_treeData->GetSelectedID() == 0)
		return; // return if nothing is selected

	Gtk::MessageDialog dialog(*this, "Are you sure you wish to remove selected item?",
			false /* use_markup */, Gtk::MESSAGE_WARNING,
			Gtk::BUTTONS_OK_CANCEL);
	dialog.set_secondary_text(
			"There is no going back after this.");

	int result = dialog.run();

	if (result == Gtk::RESPONSE_OK)
	{
		_db->RemoveItemFromDataBase(_treeData->GetSelectedID());
		_treeData->DeleteRow(_treeData->GetSelectedRowIter());
		if (_db->GetSize() == 0)
		{
			_launchButton.set_sensitive(0);
		}
	}
}

bool MainWindow::_OnMenuButton(GdkEventButton* event)
{ 
	if(_popupMenu)
		_popupMenu->popup(event->button, event->time);

	return true; //It has been handled.
}

void MainWindow::_OnButtonPreferences()
{
	PreferencesDialog pref;
	pref.LaunchDialog();
}

void MainWindow::_OnButtonQuit()
{
	hide();
}

void MainWindow::_StartTracking(unsigned int selectedID)
{
	// obtain reference to original item
	_activeDataItem = &_db->GetItem(selectedID);

	_activeDataItem->AddNewRun(std::chrono::system_clock::now());

	if (_activeDataItem->continuous)
	{
		_UpdateStartButtonText(1);
		Glib::signal_timeout().connect( sigc::mem_fun(*this, &MainWindow::_UpdateStatusLabel), 1000 );
	}
	else
	{
		_StopTracking();
	}
}

void MainWindow::_StopTracking()
{
	if (!_activeDataItem) {
		Global::Log.Add("CRITICAL! Stopping timer can't find _activeDataItem.");
		_buttonStatusLabel.set_text("Something went very wrong :(");
		return;
	}
	else if (_activeDataItem->continuous)
	{
		_activeDataItem->ChangeEndPoint(_activeDataItem->lastRunTime, std::chrono::system_clock::now());

		_UpdateStartButtonText(1);
	}

	_db->UpdateItemStats(_activeDataItem->ID);
	_treeData->UpdateRow(_treeData->GetRowIterFromID(_activeDataItem->ID));

	_activeDataItem = NULL; 

	_UpdateStatusLabel();
	_UpdateStatistics(_db->GetItem(_treeData->GetSelectedID()));

	if (Global::Config.GetAppOptions().autoSave)
		Global::Config.SaveEverything(_db);
}

void MainWindow::_TreeViewSelectionChanged()
{
	unsigned int ID = _treeData->GetSelectedID();
	DataItem* selectedDataItem = _db->GetIDDataCopy(ID);

	// GetIDDataCopy returns NULL if it doesn't find ID
	if (selectedDataItem)
	{
		_UpdateStatistics(*selectedDataItem);
		_UpdateStartButtonText(selectedDataItem->continuous);
	}
}

void MainWindow::_UpdateStartButtonText(bool continuous)
{
	if (_activeDataItem)
	{
		_launchButton.set_label("Stop");
	}
	else
	{
		if (continuous)
			_launchButton.set_label("Start");
		else
			_launchButton.set_label("Tick");
	}
}

bool MainWindow::_UpdateStatusLabel()
{
	// we only have non-NULL pointer to _activeDataItem when timer is running!
	if (!_activeDataItem)
	{
		_buttonStatusLabel.set_text("All seems quite normal.");
		return false; // returning false kills the timer
	}

	_buttonStatusLabel.set_text("Timer is running: " + Helpers::GetParsedSince(_activeDataItem->lastRunTime));

	if (Global::Config.GetAppOptions().useBell)
	{
		if ((Helpers::GetSecondsSince(_activeDataItem->lastRunTime) % Global::Config.GetAppOptions().bellPeriod) == 0)
			system(Global::Config.GetAppOptions().bellCommand.c_str());
	}

	return true;
}

void MainWindow::_UpdateStatistics(DataItem &dataItem)
{
	std::string tempValue; // used for formatting some values
	_statisticTextBuffer->erase(_statisticTextBuffer->begin(), _statisticTextBuffer->end());

	_AddKeyValueToTextView("Name: ", dataItem.name);
	_AddKeyValueToTextView("Type: ", (dataItem.continuous)? "Time" : "Instance");
	
	if (dataItem.continuous)
		_AddKeyValueToTextView("Total Time: ", Helpers::ParseShortTime(dataItem.GetTotal()));

	tempValue = dataItem.GetParsedStringFromDataType(dataItem.GetAveragePerTimeFrame()), " per " + Helpers::GetTimeFrameTypeName(dataItem.goalTimeFrame);
	_AddKeyValueToTextView("Average: ", tempValue, " (goal: " + dataItem.GetParsedStringFromDataType(dataItem.goal) + ")");

	if ((dataItem.GetTimes() != 0) && (dataItem.continuous))
		tempValue = std::string(" (about ") + Helpers::ParseShortTime(dataItem.GetTotal()/dataItem.GetTimes()) + " on average)";
	else 
		tempValue = "";
	_AddKeyValueToTextView("Instances: ", std::to_string(dataItem.GetTimes()), tempValue);

	tempValue = "per " + Helpers::GetTimeFrameTypeName(dataItem.goalTimeFrame);
	_AddKeyValueToTextView("Time Frame: ", tempValue);

	if (dataItem.firstRunTime.time_since_epoch().count() != 0)
		_AddKeyValueToTextView("First Time: ", Helpers::ParseLongTime(dataItem.firstRunTime), " (" + Helpers::GetParsedSince(dataItem.firstRunTime) + " ago)");
	if (dataItem.lastRunTime.time_since_epoch().count() != 0)
	_AddKeyValueToTextView("Last Time: ", Helpers::ParseLongTime(dataItem.lastRunTime), " (" + Helpers::GetParsedSince(dataItem.lastRunTime) + " ago)");

	_AddKeyValueToTextView("\nDescription: ", dataItem.description);
}

void MainWindow::_AddKeyValueToTextView(const std::string key, const std::string value, const std::string suffix)
{
	_statisticTextBuffer->insert(_statisticTextBuffer->end(), key);
	_statisticTextBuffer->insert_with_tag(_statisticTextBuffer->end(), value, _boldedTextTag);
	_statisticTextBuffer->insert(_statisticTextBuffer->end(), " " + suffix + "\n");
}


