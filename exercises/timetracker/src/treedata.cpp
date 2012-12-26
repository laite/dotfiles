/*										
 * treedata.cpp	
 * (c) Markus Klinga
 * 
 */

#include "treedata.h"
#include "data.h"
#include "window.h"


TreeData::TreeData(Gtk::TreeView *originalTree, DataBase *db)
{
	_treeView = originalTree;
	_db = db;
	_refTreeModel = Gtk::ListStore::create(_columns);
	_refTreeSelection = _treeView->get_selection();
}

unsigned int TreeData::GetSelectedID()
{
	unsigned int ID = 0;
	Gtk::TreeModel::iterator iter = _refTreeSelection->get_selected();

	if(iter) //If anything is selected
		ID = (*iter)[_columns.columnID];
	
	return ID;
}

Gtk::TreeModel::Row TreeData::GetSelectedRow()
{
	Gtk::TreeModel::iterator iter = _refTreeSelection->get_selected();

	return (*iter);
}

Gtk::TreeModel::Row TreeData::GetRowFromID(unsigned int ID)
{
	
}

void TreeData::ChangeRow(Gtk::TreeModel::Row &row, DataItem &dataItem)
{
	_db->PopulateRow(row, _columns, dataItem);
}

void TreeData::UpdateRow(Gtk::TreeModel::Row &row)
{
	_db->PopulateRow(row, _columns, _db->GetItem(row[_columns.columnID]));
}

ModelColumns& TreeData::Columns()
{
	return _columns;
}
Glib::RefPtr<Gtk::ListStore>& TreeData::RefTreeModel()
{
	return _refTreeModel;
}
Glib::RefPtr<Gtk::TreeSelection>& TreeData::RefTreeSelection()
{
	return _refTreeSelection;
}


/*
 *  ModelColumns
 */

ModelColumns::ModelColumns()
{
	add(columnID);
	add(columnName);
	add(columnElapsedTime);
	add(columnGoalTime);
	add(columnPercentage);
}
