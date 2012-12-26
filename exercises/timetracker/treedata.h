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

		/*
		 *  Public Functions
		 */
		
		unsigned int GetSelectedID();
		Gtk::TreeModel::Row GetRowFromID(unsigned int);
		Gtk::TreeModel::Row GetSelectedRow();
		void ChangeRow(Gtk::TreeModel::Row&, DataItem&);
		void UpdateRow(Gtk::TreeModel::Row&);

		void PopulateRow(Gtk::TreeModel::Row&, const DataItem&);
		void PopulateTreeModel();
		
		ModelColumns& Columns();
		Glib::RefPtr<Gtk::ListStore>& GetRefTreeModel();
		Glib::RefPtr<Gtk::TreeSelection>& GetRefTreeSelection();


	private:

		/*
		 *  Private members
		 */
		
		DataBase *_db;
		Gtk::TreeView *_treeView;
		Glib::RefPtr<Gtk::ListStore> _refTreeModel;
		Glib::RefPtr<Gtk::TreeSelection> _refTreeSelection;
		ModelColumns _columns;
};

#endif /* end TREEDATA_H */
