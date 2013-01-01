/*										
 * treedata.h	
 * (c) Markus Klinga
 * 
 */

#ifndef TIMETRACKER_TREEDATA_H
#define TIMETRACKER_TREEDATA_H

#include <gtkmm.h>
#include <map>

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
		void InitializeTreeView();
		
		unsigned int GetSelectedID();
		Gtk::TreeModel::Row GetRowFromID(unsigned int);
		Gtk::TreeModel::Row GetSelectedRow();
		void UpdateRow(Gtk::TreeModel::Row&);
		void AddRow(const DataItem&, bool rebuildRowMap = true);
		void DeleteRow(Gtk::TreeModel::iterator);

		void PopulateRow(Gtk::TreeModel::Row&, const DataItem&);
		void PopulateTreeModel();
		
		ModelColumns& Columns();
		Glib::RefPtr<Gtk::ListStore>& GetRefTreeModel();
		Glib::RefPtr<Gtk::TreeSelection>& GetRefTreeSelection();


	private:
		
		/*
		 *  Private functions
		 */

		void _RebuildRowMap();
		
		/*
		 *  Private members
		 */
		
		DataBase *_db;
		Gtk::TreeView *_treeView;
		Glib::RefPtr<Gtk::ListStore> _refTreeModel;
		Glib::RefPtr<Gtk::TreeSelection> _refTreeSelection;
		std::map<unsigned int, Gtk::TreeModel::iterator> _rowMap;
		ModelColumns _columns;
};

#endif /* end TREEDATA_H */
