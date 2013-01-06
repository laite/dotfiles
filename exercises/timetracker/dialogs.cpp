/*										
 * dialogs.cpp	
 * (c) Markus Klinga
 * 
 * Handles all secondary windows
 */

#include "data.h"
#include "dialogs.h"
#include "helpers.h"

DataItemDialog::DataItemDialog():
	_nameLabel("Name: "),
	_descriptionLabel("Description: "),
	_inverseButton("Inverse goal"),
	_goalLabel("Goal: "),
	_goalPerLabel("In: ")
{
	Gtk::Box* dialogArea = this->get_content_area();
	dialogArea->set_orientation(Gtk::ORIENTATION_VERTICAL);
	dialogArea->set_spacing(5);

	_goalButton.set_adjustment(Gtk::Adjustment::create(45.0, 1.0, 770.0, 1.0, 10.0));
	
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

	_goalTimeFrame.append(Helpers::GiveTimeFrameType(Global::GOAL_TIMEFRAME_DAY));
	_goalTimeFrame.append(Helpers::GiveTimeFrameType(Global::GOAL_TIMEFRAME_WEEK));
	_goalTimeFrame.append(Helpers::GiveTimeFrameType(Global::GOAL_TIMEFRAME_MONTH));
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

	// clear all items since we don't allow changing status of 'continuous'
	_goalType.remove_all();

	if (dataItem.continuous)
	{
		_goalType.append("minutes");
		_goalType.append("hours");
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
		_goalType.append("instances");
		_goalButton.set_value(dataItem.goal);
		_goalType.set_active_text("instances");
	}
	_goalTimeFrame.set_active(dataItem.goalTimeFrame);

}
