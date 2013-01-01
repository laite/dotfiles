/*										
 * dialogs.cpp	
 * (c) Markus Klinga
 * 
 * Handles all secondary windows
 */

#include "data.h"
#include "dialogs.h"

NewDataItemDialog::NewDataItemDialog():
	_nameLabel("Name "),
	_descriptionLabel("Description "),
	_inverseButton("Inverse"),
	_continuousButton("Measure instances instead of time"),
	_goalLabel("Goal (minutes per day)")
{
	Gtk::Box* dialogArea = this->get_content_area();
	dialogArea->set_orientation(Gtk::ORIENTATION_VERTICAL);
	dialogArea->set_spacing(5);

	_goalButton.set_adjustment(Gtk::Adjustment::create(45.0, 1.0, 770.0, 1.0, 10.0));
	
	/*
	 *  Widgets 
	 */
	
	_nameRow.pack_start(_nameLabel);
	_nameRow.pack_start(_nameEntry);
	dialogArea->pack_start(_nameRow);

	_descriptionRow.pack_start(_descriptionLabel);
	_descriptionRow.pack_start(_descriptionEntry);
	dialogArea->pack_start(_descriptionRow);

	_goalRow.pack_start(_goalLabel);
	_goalRow.pack_start(_goalButton);
	dialogArea->pack_start(_goalRow);

	dialogArea->pack_start(_continuousButton);
	dialogArea->pack_start(_inverseButton);

	this->add_button("OK", Gtk::RESPONSE_OK);
	this->add_button("Cancel", Gtk::RESPONSE_CANCEL);
	this->show_all_children();
}

int NewDataItemDialog::LaunchDialog()
{
	DataItem dItem;
	int result = this->run();

	if (result == Gtk::RESPONSE_OK)
	{
		std::string nameText = _nameEntry.get_text();
		if (nameText.size() == 0)
			nameText = "[empty]";
		dItem.name = nameText;

		std::string descriptionText = _descriptionEntry.get_text();
		if (descriptionText.size() == 0)
			descriptionText = "[empty]";
		dItem.description = descriptionText;

		dItem.continuous = !_continuousButton.get_active();
		dItem.inverse = _inverseButton.get_active();
	}

	_newItem = dItem;

	return result;
}

DataItem NewDataItemDialog::GetItem()
{
	return _newItem;
}
