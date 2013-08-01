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

		Gtk::HBox _beginDateRow, _endDateRow;
		Gtk::HBox _beginTimeRow, _endTimeRow;
		Gtk::HBox _totalRow;

		Gtk::Label _descriptionLabel;
		Gtk::Label _totalHourLabel, _totalMinLabel;

		Gtk::Label _beginDateLabel, _endDateLabel, _totalLabel;
		Gtk::Label _beginTimeLabel, _endTimeLabel;

		Gtk::SpinButton _beginDaySpin, _beginMonthSpin, _beginYearSpin, _beginHourSpin, _beginMinSpin;
		Gtk::SpinButton _endDaySpin, _endMonthSpin, _endYearSpin, _endHourSpin, _endMinSpin;
		Gtk::SpinButton _totalHourSpin, _totalMinSpin;


		/*
		 * Private Functions
		 */


		/*
		 * _InitValues sets all spins to 'now'
		 */

		void _InitValues();

		/* 
		 * _SetTotal checks both _beginEntry and _endEntry,
		 * and calculates Total values from them
		 * If either entry is invalid, total-spinbuttons are set to 0
		 */

		bool _SetTotal(GdkEventFocus *e);

		/* 
		 * _SetEndTime sets ending time spins according to
		 * _beginSpins + totalHours + totalMinutes
		 * (this allows user to modify total- time instead of calculating end point manually)
		 */

		void _SetEndTime();

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

		Gtk::CheckButton _autoSaveButton;

		// these here define 'default' values for new items
		// they can later be changed on 'item settings'
		Gtk::CheckButton _useBellButton;
		Gtk::Entry _bellCommandEntry;

		Gtk::HBox _bellPeriodBox;
		Gtk::SpinButton _bellPeriodButton;
		Gtk::Label _bellPeriodLabel;

		/*
		 *  Other private members
		 */
		
};

#endif /* end DIALOGS_H */
