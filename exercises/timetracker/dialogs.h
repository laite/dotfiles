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

#endif /* end DIALOGS_H */
