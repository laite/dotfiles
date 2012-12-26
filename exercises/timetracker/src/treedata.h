/*										
 * treedata.h	
 * (c) Markus Klinga
 * 
 */

#ifndef TREEDATA_H
#define TREEDATA_H

#include <gtkmm.h>

class DataBase;
class DataItem;
/*
 *  Model Columns
 */

class ModelColumns : public Gtk::TreeModel::ColumnRecord
{
	public:

		ModelColumns();

		Gtk::TreeModelColumn<unsigned int> columnID;
		Gtk::TreeModelColumn<Glib::ustring> columnName;
		Gtk::TreeModelColumn<int> columnPercentage;
		Gtk::TreeModelColumn<long> columnElapsedTime;
		Gtk::TreeModelColumn<int> columnGoalTime;
};


class TreeData 
{
	public:

		TreeData(Gtk::TreeView *, DataBase *);
		unsigned int GetSelectedID();
		Gtk::TreeModel::Row GetRowFromID(unsigned int);
		Gtk::TreeModel::Row GetSelectedRow();
		void ChangeRow(Gtk::TreeModel::Row&, DataItem&);
		void UpdateRow(Gtk::TreeModel::Row&);

		ModelColumns& Columns();
		Glib::RefPtr<Gtk::ListStore>& RefTreeModel();
		Glib::RefPtr<Gtk::TreeSelection>& RefTreeSelection();


	private:

		ModelColumns _columns;

		DataBase *_db;
		Gtk::TreeView *_treeView;
		Glib::RefPtr<Gtk::ListStore> _refTreeModel;
		Glib::RefPtr<Gtk::TreeSelection> _refTreeSelection;
		
};

#endif /* end TREEDATA_H */
