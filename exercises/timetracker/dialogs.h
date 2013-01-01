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

class NewDataItemDialog : public Gtk::Dialog
{
	public:
		NewDataItemDialog();

		int LaunchDialog();
		DataItem GetItem();

	private:

		Gtk::HBox _nameRow;
		Gtk::Label _nameLabel;
		Gtk::Entry _nameEntry;

		Gtk::HBox _descriptionRow;
		Gtk::Label _descriptionLabel;
		Gtk::Entry _descriptionEntry;

		Gtk::CheckButton _inverseButton;
		Gtk::CheckButton _continuousButton;

		Gtk::HBox _goalRow;
		Gtk::Label _goalLabel;
		Gtk::SpinButton _goalButton;


		DataItem _newItem;
};

#endif /* end DIALOGS_H */
