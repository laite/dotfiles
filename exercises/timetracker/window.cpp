/*										
 * window.cpp	
 * (c) Markus Klinga
 * 
 * Definitions of MainWindow
 */

#include <iostream>
#include <ctime>
#include <chrono>
#include "log.h"
#include "window.h"
#include "data.h" // need DataBase class implementation
#include "treedata.h"
#include "dialogs.h"

MainWindow::MainWindow(DataBase *d): 
	_db(d), // main database
	_mainVBox(Gtk::ORIENTATION_VERTICAL),
	_contentVBox(Gtk::ORIENTATION_VERTICAL),
	_buttonQuit("Quit"), _buttonNew("New"), _buttonRemove("Remove"), _buttonStart("Start"), _buttonStop("Stop"),
	_isTracking(false)
{

	set_title("TimeTracker/laite");
	set_border_width(5);
	set_default_size(800, 450);

	/*
	 *  Containers and widgets
	 *
	 *  contentVBox
	 */
	
	_treeViewScrollWindow.add(_treeView);
	_treeViewScrollWindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC); //Only show the scrollbars when they are necessary:

	_textViewScrollWindow.add(_statisticTextView);
	_textViewScrollWindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC); //Only show the scrollbars when they are necessary:

	_contentVPaned.add1(_treeViewScrollWindow);
	_contentVPaned.add2(_textViewScrollWindow);
	_contentVPaned.set_position(225);

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
	 *  Buttons
	 */
	
	_buttonBox.pack_start(_buttonStart, Gtk::PACK_SHRINK);
	_buttonBox.pack_start(_buttonStop, Gtk::PACK_SHRINK);
	_buttonBox.pack_start(_buttonNew, Gtk::PACK_SHRINK);
	_buttonBox.pack_start(_buttonRemove, Gtk::PACK_SHRINK);
	_buttonBox.pack_start(_buttonQuit, Gtk::PACK_SHRINK);

	_buttonBox.set_border_width(5);
	_buttonBox.set_layout(Gtk::BUTTONBOX_END);

	/*
	 *  MainVBox
	 */

	add(_mainVBox); // the main VBox
	_mainVBox.pack_start(_buttonBox, Gtk::PACK_SHRINK);
	_mainVBox.pack_start(_contentVBox);

	/*
	 *  Widget rules
	 */

	_treeData = new TreeData(&_treeView, _db);
	_treeData->InitializeTreeView();
	_treeData->PopulateTreeModel();

	_buttonStop.set_sensitive(false); // disable stop button by default
	
	/*
	 *  Add signals
	 */
	
	_buttonQuit.signal_clicked().connect( sigc::mem_fun(*this, &MainWindow::_OnButtonQuit) );
	_buttonNew.signal_clicked().connect( sigc::mem_fun(*this, &MainWindow::_OnButtonNew) );
	_buttonRemove.signal_clicked().connect( sigc::mem_fun(*this, &MainWindow::_OnButtonRemove) );
	_buttonStart.signal_clicked().connect( sigc::mem_fun(*this, &MainWindow::_OnButtonStart) );
	_buttonStop.signal_clicked().connect( sigc::mem_fun(*this, &MainWindow::_OnButtonStop) );

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
		_buttonStart.set_sensitive(0);
		_buttonRemove.set_sensitive(0);
	}
	
	/*
	 *  Release
	 */
	
	show_all_children();

}

MainWindow::~MainWindow()
{
	Log.Add("Killing MainWindow");
}

void MainWindow::_OnButtonStart()
{
	int selectedID = _treeData->GetSelectedID();

	// See if there's an ID, and it exists in _db
	if ((selectedID == 0) || (!_db->IsIn(selectedID))) {
		Log.Add("* ERROR * Can not find item with ID = " + std::to_string(selectedID));
		return;
	}

	// obtain reference to original item
	_activeDataItem = &_db->GetItem(selectedID);

	_timerBeginPoint = std::chrono::system_clock::now();
	_activeDataItem->lastTime = _timerBeginPoint;

	// Set also to first time if needed
	if (_activeDataItem->firstTime.time_since_epoch().count() == 0)
		_activeDataItem->firstTime = _timerBeginPoint;

	_isTracking = true;
	_buttonStart.set_sensitive(false);
	_buttonStop.set_sensitive(true);
	Log.Add("Started timer for " + _activeDataItem->name);
}

void MainWindow::_OnButtonStop()
{
	std::chrono::steady_clock::time_point endPoint = std::chrono::steady_clock::now();
	std::chrono::duration<int> timeSpan = std::chrono::duration_cast<std::chrono::duration<int>>(endPoint -_timerBeginPoint);

	if (!_activeDataItem) {
		Log.Add("CRITICAL! Stopping timer can't find _activeDataItem.");
	}
	else {
		_activeDataItem->elapsedTime += timeSpan.count();
		++_activeDataItem->times;
		_activeDataItem->description = "This just in.";
		_db->UpdateItemStats(_activeDataItem->ID);
		_treeData->UpdateRow(_treeData->GetRowIterFromID(_activeDataItem->ID));
	}

	Log.Add("Stopping timer after " + std::to_string(timeSpan.count()) + " seconds.");
	_buttonStart.set_sensitive(true);
	_buttonStop.set_sensitive(false);
	_isTracking = false;
	_activeDataItem = NULL; // nullify the pointer

	_UpdateStatistics(_db->GetItem(_treeData->GetSelectedID()));
}

void MainWindow::_OnButtonNew()
{
	NewDataItemDialog dialog;

	if (dialog.LaunchDialog() == Gtk::RESPONSE_OK)
	{
		Log.Add("NewItemDialog gives OK.");
		DataItem newItem = dialog.GetItem();
		_db->AddItemToDataBase(newItem);
		_treeData->AddRow(newItem, true);
		_buttonStart.set_sensitive(1);
		_buttonRemove.set_sensitive(1);
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
			_buttonStart.set_sensitive(0);
			_buttonRemove.set_sensitive(0);
		}
	}
}

void MainWindow::_OnButtonQuit()
{
	hide();
}

void MainWindow::_TreeViewSelectionChanged()
{
	unsigned int ID = _treeData->GetSelectedID();
	DataItem* selectedDataItem = _db->GetIDDataCopy(ID);

	// GetIDDataCopy returns NULL if it doesn't find ID
	if (selectedDataItem)
		_UpdateStatistics(*selectedDataItem);
}

void MainWindow::_UpdateStatistics(DataItem &dataItem)
{
	// dataitem has following properties: ID, name, description, percentage 
	// continuous, elapsedTime, times, lastTime, goalTime
	
	std::string tempValue; // used for formatting some values

	_statisticTextBuffer->erase(_statisticTextBuffer->begin(), _statisticTextBuffer->end());

	_AddKeyValueToTextView("Name: ", dataItem.name);

	tempValue = (dataItem.continuous)? "Time" : "Instance";
	_AddKeyValueToTextView("Type: ", tempValue);
	
	
	_AddKeyValueToTextView("First Time: ", _GetTimePointTextWithDaysAgo(dataItem.firstTime)); 
	_AddKeyValueToTextView("Last Time: ", _GetTimePointTextWithDaysAgo(dataItem.lastTime)); 

	_AddKeyValueToTextView("\nDescription: ", dataItem.description);
}


void MainWindow::_AddKeyValueToTextView(const std::string key, const std::string value)
{
	_statisticTextBuffer->insert(_statisticTextBuffer->end(), key);
	_statisticTextBuffer->insert_with_tag(_statisticTextBuffer->end(), value + " \n", _boldedTextTag);
}

std::string MainWindow::_GetTimePointTextWithDaysAgo(std::chrono::steady_clock::time_point &timePoint)
{
	std::chrono::system_clock::duration dtn = timePoint.time_since_epoch();

	if (dtn.count() == 0)
		return "Never";

	std::string formattedString;
	std::time_t temp_t = std::chrono::system_clock::to_time_t (timePoint);

	formattedString = ctime(&temp_t);
	formattedString = formattedString.substr(0, formattedString.length() - 1); // remove \n from the end
	std::chrono::duration<int,std::ratio<60*60*24> > timeAgo = std::chrono::duration_cast< std::chrono::duration<int,std::ratio<60*60*24> > >(std::chrono::system_clock::now() - timePoint);
	
	formattedString = formattedString + " (" + std::to_string(timeAgo.count()) + " days ago)";

	return formattedString;
}

