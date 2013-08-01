/*										
 * dialogs.h	
 * (c) Markus Klinga
 * 
 * Handles all secondary windows
 */

#ifndef TIMETRACKER_DIALOGS_H
#define TIMETRACKER_DIALOGS_H

#include <gtkmm.h>

class DataItem;

class DataItemDialog : public Gtk::Dialog
{
	public:

		DataItemDialog();

		int LaunchDialog(DataItem *);

	private:

		Gtk::HBox _mainRow;
		Gtk::VBox _titleColumn;
		Gtk::VBox _widgetColumn;
		Gtk::Label _nameLabel;
		Gtk::Entry _nameEntry;

		Gtk::Label _descriptionLabel;
		Gtk::Entry _descriptionEntry;

		Gtk::CheckButton _inverseButton;

		Gtk::HBox _goalRow;
		Gtk::SpinButton _goalButton;
		Gtk::Label _goalLabel, _goalPerLabel;
		Gtk::ComboBoxText _goalType;
		Gtk::ComboBoxText _goalTimeFrame;

		void _FillDialogValues(DataItem&);

		DataItem _dataItem;
};

class AddTimeDialog : public Gtk::Dialog
{
	public:

		AddTimeDialog();

		int LaunchDialog(DataItem *);

	private:

		Gtk::VBox _mainColumn;

		Gtk::HBox _widgetColumnsRow;
		Gtk::VBox _titleColumn;
		Gtk::VBox _widgetColumn;

		Gtk::HBox _beginDateRow, _beginTimeRow;
		Gtk::HBox _totalRow;

		Gtk::Label _descriptionLabel;
		Gtk::Label _totalHourLabel, _totalMinLabel;

		Gtk::Label _beginDateLabel, _beginTimeLabel, _totalLabel;

		Gtk::SpinButton _beginDaySpin, _beginMonthSpin, _beginYearSpin, _beginHourSpin, _beginMinSpin;
		Gtk::SpinButton _totalHourSpin, _totalMinSpin;


		/*
		 * Private Functions
		 */


		/*
		 * _InitValues sets all spins to 'now'
		 */

		void _InitValues();

		std::pair<long, long> _CalculateTimePoints();
		/* 
		 * Private members
		 */

		DataItem _dataItem;
};


class PreferencesDialog : public Gtk::Dialog 
{
	public:

		PreferencesDialog();

		int LaunchDialog();

	private:
		
		/*
		 *  Private Methods
		 */

		void _FillDialogValues();
		
		/*
		 *  Widgets in dialog
		 */
		
		Gtk::CheckButton _useShortTimeFormatButton;

		Gtk::CheckButton _useCustomDateTimeButton;
		Gtk::Label _customDateTimeLabel;
		Gtk::Entry _customDateTimeFormatEntry;
};

#endif /* end DIALOGS_H */
