/*										
 * dialogs.cpp	
 * (c) Markus Klinga
 * 
 * Handles all secondary windows
 */

#include "data.h"
#include "dialogs.h"
#include "helpers.h"
#include "config.h"

DataItemDialog::DataItemDialog()
	: _nameLabel("Name: ")
	, _descriptionLabel("Description: ")
	, _inverseButton("Inverse goal")
	, _goalLabel("Goal: ")
	, _goalPerLabel("In: ")
{
	Gtk::Box* dialogArea = this->get_content_area();
	dialogArea->set_orientation(Gtk::ORIENTATION_VERTICAL);
	dialogArea->set_spacing(5);

	_goalButton.set_adjustment(Gtk::Adjustment::create(45.0, 0.0, 770.0, 1.0, 10.0));
	
	/*
	 *  Widgets 
	 */

	_titleColumn.set_spacing(5);
	_widgetColumn.set_spacing(5);

	_nameLabel.set_alignment(0.0, 0.5);
	_goalLabel.set_alignment(0.0, 0.5);
	_goalPerLabel.set_alignment(0.0, 0.5);
	_descriptionLabel.set_alignment(0.0, 0.5);

	_nameLabel.set_margin_left(10);
	_nameLabel.set_margin_right(10);
	_goalLabel.set_margin_left(10);
	_goalLabel.set_margin_right(10);
	_goalPerLabel.set_margin_left(10);
	_goalPerLabel.set_margin_right(10);
	_descriptionLabel.set_margin_left(10);
	_descriptionLabel.set_margin_right(10);


	_titleColumn.pack_start(_nameLabel, true, true);
	_widgetColumn.pack_start(_nameEntry, Gtk::PACK_EXPAND_PADDING);

	_titleColumn.pack_start(_descriptionLabel, Gtk::PACK_EXPAND_PADDING);
	_widgetColumn.pack_start(_descriptionEntry, Gtk::PACK_EXPAND_PADDING);

	_titleColumn.pack_start(_goalLabel, Gtk::PACK_EXPAND_PADDING);
	_goalRow.pack_start(_goalButton);
	_goalRow.pack_start(_goalType);

	_widgetColumn.pack_start(_goalRow, Gtk::PACK_EXPAND_PADDING);
	_titleColumn.pack_start(_goalPerLabel, Gtk::PACK_EXPAND_PADDING);
	_widgetColumn.pack_start(_goalTimeFrame, Gtk::PACK_EXPAND_PADDING);

	_mainRow.pack_start(_titleColumn, Gtk::PACK_SHRINK);
	_mainRow.pack_start(_widgetColumn, Gtk::PACK_EXPAND_WIDGET);

	dialogArea->pack_start(_mainRow);

	_goalType.append("minutes");
	_goalType.append("hours");
	_goalType.append("instances");
	_goalType.set_active(0);

	_goalTimeFrame.append(Helpers::GetTimeFrameTypeName(Global::GOAL_TIMEFRAME_DAY));
	_goalTimeFrame.append(Helpers::GetTimeFrameTypeName(Global::GOAL_TIMEFRAME_WEEK));
	_goalTimeFrame.append(Helpers::GetTimeFrameTypeName(Global::GOAL_TIMEFRAME_MONTH));
	_goalTimeFrame.append(Helpers::GetTimeFrameTypeName(Global::GOAL_TIMEFRAME_NONE));
	_goalTimeFrame.set_active(0);

	dialogArea->pack_start(_inverseButton);

	this->add_button("OK", Gtk::RESPONSE_OK);
	this->add_button("Cancel", Gtk::RESPONSE_CANCEL);
	this->show_all_children();
}

int DataItemDialog::LaunchDialog(DataItem *dataItem)
{
	if (dataItem == NULL)
		dataItem = &_dataItem;
	else
		_FillDialogValues(*dataItem);

	int result = this->run();

	if (result == Gtk::RESPONSE_OK)
	{
		std::string nameText = _nameEntry.get_text();
		if (nameText.size() == 0)
			nameText = "[empty]";
		dataItem->name = nameText;

		std::string descriptionText = _descriptionEntry.get_text();
		if (descriptionText.size() == 0)
			descriptionText = "[empty]";
		dataItem->description = descriptionText;

		dataItem->inverse = _inverseButton.get_active();

		dataItem->goal= _goalButton.get_value();

		// get_act..ber() returns -1 if nothing is active
		dataItem->goalTimeFrame = std::max(0, _goalTimeFrame.get_active_row_number());

		if (_goalType.get_active_text() == "instances")
			dataItem->continuous = false;
		else
		{
			dataItem->continuous = true;
			if (_goalType.get_active_text() == "minutes")
				dataItem->goal *= 60;
			else if (_goalType.get_active_text() == "hours")
				dataItem->goal *= 60*60;
		}
	}

	return result;
}

void DataItemDialog::_FillDialogValues(DataItem &dataItem)
{
	_nameEntry.set_text(dataItem.name);
	_descriptionEntry.set_text(dataItem.description);
	_inverseButton.set_active(dataItem.inverse);

	// we don't allow changing status of 'continuous'
	// for items that already have history
	if (dataItem.GetTotal() != 0)
	{
		_goalType.remove_all();
		if (dataItem.continuous)
		{
			_goalType.append("minutes");
			_goalType.append("hours");
		}
		else
			_goalType.append("instances");
	}

	if (dataItem.continuous)
	{
		if (dataItem.goal >= 18000) { // greater than 5h shows as 'hours'
			_goalButton.set_value(dataItem.goal/3600);
			_goalType.set_active_text("hours");
		}
		else {
			_goalButton.set_value(dataItem.goal/60);
			_goalType.set_active_text("minutes");
		}
	}
	else
	{
		_goalButton.set_value(dataItem.goal);
		_goalType.set_active_text("instances");
	}
	_goalTimeFrame.set_active(dataItem.goalTimeFrame);

}


/*
 * AddTimeDialog
 */


AddTimeDialog::AddTimeDialog()
	: _descriptionLabel("Select timepoints for new action")
	, _beginDateLabel("Begin date: ")
	, _beginTimeLabel("Begin time: ")
	, _totalHourLabel("h")
	, _totalMinLabel("min")
	, _totalLabel("Duration: ")
{
	Gtk::Box* dialogArea = this->get_content_area();
	dialogArea->set_orientation(Gtk::ORIENTATION_VERTICAL);
	dialogArea->set_spacing(5);

	//_beginEntry.set_text(Helpers::ParseLongTime(std::chrono::system_clock::now()));

	// TODO: disable end date on non-continuous dataitems
	//_endEntry.set_text(Helpers::ParseLongTime(std::chrono::system_clock::now()));


	/*
	 *  Widgets 
	 */


	_mainColumn.set_spacing(5);

	/* Spins */

	_beginYearSpin.set_adjustment(Gtk::Adjustment::create(0, 2000.0, 2027.0, 1.0, 10.0));
	_beginMonthSpin.set_adjustment(Gtk::Adjustment::create(0, 1.0, 12.0, 1.0, 2.0));
	_beginDaySpin.set_adjustment(Gtk::Adjustment::create(0, 1.0, 31.0, 1.0, 10.0));
	_beginHourSpin.set_adjustment(Gtk::Adjustment::create(0, 0.0, 23.0, 1.0, 10.0));
	_beginMinSpin.set_adjustment(Gtk::Adjustment::create(0, 0.0, 59.0, 1.0, 10.0));

	_totalHourSpin.set_adjustment(Gtk::Adjustment::create(0, 0.0, 336.0, 1.0, 10.0));
	_totalMinSpin.set_adjustment(Gtk::Adjustment::create(0, 0.0, 59.0, 1.0, 10.0));

	/* Signals */

	//_beginDaySpin.signal_focus_out_event().connect( sigc::mem_fun(*this, &AddTimeDialog::_SetTotal));

	/*
	 * Packing
	 */


	_mainColumn.pack_start(_descriptionLabel, true, true);

	_beginDateRow.pack_start(_beginDaySpin);
	_beginDateRow.pack_start(_beginMonthSpin);
	_beginDateRow.pack_start(_beginYearSpin);
	_beginTimeRow.pack_start(_beginHourSpin);
	_beginTimeRow.pack_start(_beginMinSpin);

	_titleColumn.pack_start(_beginDateLabel, true, true);
	_widgetColumn.pack_start(_beginDateRow, Gtk::PACK_EXPAND_PADDING);

	_titleColumn.pack_start(_beginTimeLabel, true, true);
	_widgetColumn.pack_start(_beginTimeRow, Gtk::PACK_EXPAND_PADDING);

	_titleColumn.pack_start(_totalLabel, Gtk::PACK_EXPAND_PADDING);

	_totalRow.pack_start(_totalHourSpin);
	_totalRow.pack_start(_totalHourLabel);
	_totalRow.pack_start(_totalMinSpin);
	_totalRow.pack_start(_totalMinLabel);

	_widgetColumn.pack_start(_totalRow, Gtk::PACK_EXPAND_PADDING);

	_widgetColumnsRow.pack_start(_titleColumn, Gtk::PACK_SHRINK);
	_widgetColumnsRow.pack_start(_widgetColumn, Gtk::PACK_EXPAND_WIDGET);

	_mainColumn.pack_start(_widgetColumnsRow, Gtk::PACK_EXPAND_WIDGET);

	dialogArea->pack_start(_mainColumn);

	this->add_button("OK", Gtk::RESPONSE_OK);
	this->add_button("Cancel", Gtk::RESPONSE_CANCEL);
	this->show_all_children();
}

int AddTimeDialog::LaunchDialog(DataItem *dataItem)
{
	if (dataItem == NULL)
		dataItem = &_dataItem;

	_InitValues();

	int result = this->run();

	// TODO: don't allow future times?
	if (result == Gtk::RESPONSE_OK)
	{
		// Obtain timePoints
		std::pair<long, long> timePoints = _CalculateTimePoints();
		Global::Log.Add("New timepoints: " + std::to_string(timePoints.first) + "/" + std::to_string(timePoints.second));

		std::chrono::system_clock::time_point beginPoint(std::chrono::seconds(timePoints.first));
		std::chrono::system_clock::time_point endPoint(std::chrono::seconds(timePoints.second));

		// Add timepoints to dataItem
		dataItem->AddNewRun(beginPoint);

		if (dataItem->continuous)
			dataItem->ChangeEndPoint(beginPoint, endPoint);
	}

	return result;
}

std::pair<long, long> AddTimeDialog::_CalculateTimePoints()
{
	std::time_t endTimeT = time(NULL), beginTimeT = time(NULL);
	std::tm endTm = *std::localtime(&endTimeT), beginTm = *std::localtime(&beginTimeT);

	// set both Tm's to begin time at first
	beginTm.tm_year = _beginYearSpin.get_value() - 1900;
	beginTm.tm_mon = _beginMonthSpin.get_value() - 1;
	beginTm.tm_mday = _beginDaySpin.get_value();
	beginTm.tm_hour = _beginHourSpin.get_value();
	beginTm.tm_min = _beginMinSpin.get_value();

	endTm = beginTm;

	// convert to time_t
	beginTimeT = mktime(&beginTm);
	endTimeT = mktime(&endTm);

	// add duration to end point (should be 0 for non-continuous items)
	endTimeT += _totalHourSpin.get_value()*3600;
	endTimeT += _totalMinSpin.get_value()*60;

	return std::make_pair(static_cast<long>(beginTimeT), static_cast<long>(endTimeT));
}

void AddTimeDialog::_InitValues()
{
	std::time_t t = time(NULL);
    std::tm time_tm = *std::localtime(&t);

	_beginYearSpin.set_value(time_tm.tm_year + 1900);
	_beginMonthSpin.set_value(time_tm.tm_mon + 1);
	_beginDaySpin.set_value(time_tm.tm_mday);
	_beginHourSpin.set_value(time_tm.tm_hour);
	_beginMinSpin.set_value(time_tm.tm_min);

	_totalHourSpin.set_value(0);
	_totalMinSpin.set_value(0);
}


/*
 *  PreferencesDialog
 */


PreferencesDialog::PreferencesDialog()
	: _useShortTimeFormatButton("Use short time format")
	, _autoSaveButton("Autosave")
	, _useCustomDateTimeButton("Use custom date/time format")
	, _customDateTimeLabel("Format:")
	, _useBellButton("Run external commands periodically")
	, _bellPeriodLabel("Period (min)")
{
	Gtk::Box* dialogArea = this->get_content_area();
	dialogArea->set_orientation(Gtk::ORIENTATION_VERTICAL);
	dialogArea->set_spacing(5);

	dialogArea->pack_start(_useShortTimeFormatButton);
	dialogArea->pack_start(_useCustomDateTimeButton);
	dialogArea->pack_start(_customDateTimeFormatEntry);
	dialogArea->pack_start(_autoSaveButton);
	dialogArea->pack_start(_useBellButton);
	dialogArea->pack_start(_bellCommandEntry);

	_bellPeriodBox.pack_start(_bellPeriodLabel);
	_bellPeriodBox.pack_start(_bellPeriodButton);
	dialogArea->pack_start(_bellPeriodBox);
	
	_bellPeriodButton.set_adjustment(Gtk::Adjustment::create(15.0, 1.0, 120.0, 1.0, 10.0));

	this->add_button("OK", Gtk::RESPONSE_OK);
	this->add_button("Cancel", Gtk::RESPONSE_CANCEL);
	this->show_all_children();
}

void PreferencesDialog::_FillDialogValues()
{
	_useShortTimeFormatButton.set_active(Global::Config.GetAppOptions().useShortTimeFormat);
	_useCustomDateTimeButton.set_active(Global::Config.GetAppOptions().useCustomDateTimeFormat);
	_customDateTimeFormatEntry.set_text(Global::Config.GetAppOptions().customDateTimeFormat);
	_autoSaveButton.set_active(Global::Config.GetAppOptions().autoSave);
	_useBellButton.set_active(Global::Config.GetAppOptions().useBell);
	_bellCommandEntry.set_text(Global::Config.GetAppOptions().bellCommand);
	_bellPeriodButton.set_value(Global::Config.GetAppOptions().bellPeriod/60);
}

int PreferencesDialog::LaunchDialog()
{
	_FillDialogValues();

	int result = this->run();

	if (result == Gtk::RESPONSE_OK)
	{
		Global::Config.SetAppOptions().useShortTimeFormat = _useShortTimeFormatButton.get_active();
		Global::Config.SetAppOptions().useCustomDateTimeFormat = _useCustomDateTimeButton.get_active();
		Global::Config.SetAppOptions().customDateTimeFormat = _customDateTimeFormatEntry.get_text();
		Global::Config.SetAppOptions().autoSave = _autoSaveButton.get_active();
		Global::Config.SetAppOptions().useBell = _useBellButton.get_active();
		Global::Config.SetAppOptions().bellCommand = _bellCommandEntry.get_text();
		Global::Config.SetAppOptions().bellPeriod = 60*_bellPeriodButton.get_value();
	}

	return result;
}
