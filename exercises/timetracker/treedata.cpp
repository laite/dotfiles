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

// Fill TreeView in MainWindow with data
void TreeData::PopulateTreeModel()
{
	const std::map<unsigned int, DataItem> _data = _db->GetData();
	
	//Fill the TreeView's model
	for (std::map<unsigned int, DataItem>::const_iterator dataIter = _data.begin();
			dataIter != _data.end(); ++dataIter)
	{
		Gtk::TreeModel::Row row = *(_refTreeModel->append());
		PopulateRow(row, (*dataIter).second);
	}
}

void TreeData::PopulateRow(Gtk::TreeModel::Row &row, const DataItem &ditem)
{
	row[_columns.columnID] = ditem.ID;
	row[_columns.columnName] = ditem.name;
	row[_columns.columnPercentage] = ditem.percentage;
	row[_columns.columnElapsedTime] = ditem.elapsedTime;
	row[_columns.columnGoalTime] = ditem.goalTime;
}

void TreeData::ChangeRow(Gtk::TreeModel::Row &row, DataItem &dataItem)
{
	PopulateRow(row, dataItem);
}

void TreeData::UpdateRow(Gtk::TreeModel::Row &row)
{
	PopulateRow(row, _db->GetItem(row[_columns.columnID]));
}

ModelColumns& TreeData::Columns()
{
	return _columns;
}
Glib::RefPtr<Gtk::ListStore>& TreeData::GetRefTreeModel()
{
	return _refTreeModel;
}
Glib::RefPtr<Gtk::TreeSelection>& TreeData::GetRefTreeSelection()
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
