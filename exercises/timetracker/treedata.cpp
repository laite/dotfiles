/*										
 * treedata.cpp	
 * (c) Markus Klinga
 * 
 */

#include "treedata.h"
#include "data.h"
#include "window.h"
#include "log.h"
#include "helpers.h"


TreeData::TreeData(Gtk::TreeView *originalTree, DataBase *db)
{
	_treeView = originalTree;
	_db = db;
	_refTreeModel = Gtk::ListStore::create(_columns);
	_refTreeSelection = _treeView->get_selection();
}

void TreeData::InitializeTreeView()
{
	_treeView->set_model(GetRefTreeModel());

	_treeView->append_column("ID", Columns().columnID);
	_treeView->append_column("Name", Columns().columnName);
	_treeView->append_column("Total", Columns().columnElapsedTime);
	_treeView->append_column("Goal", Columns().columnGoalTime);

	//Display a progress bar instead of a decimal number:
	Gtk::CellRendererProgress* cell = Gtk::manage(new Gtk::CellRendererProgress);
	int cols_count = _treeView->append_column("Percentage", *cell);
	Gtk::TreeViewColumn* pColumn = _treeView->get_column(cols_count - 1);
	if(pColumn)
		pColumn->add_attribute(cell->property_value(), Columns().columnPercentage);

	// make all columns reorderable and resizable
	std::vector<Gtk::TreeView::Column*> allColumns = _treeView->get_columns();
	for (std::vector<Gtk::TreeView::Column*>::iterator columnIter = allColumns.begin();
			columnIter != allColumns.end(); ++columnIter)
	{
		(*columnIter)->set_reorderable();
		(*columnIter)->set_resizable();
	}
}

unsigned int TreeData::GetSelectedID()
{
	unsigned int ID = 0;
	Gtk::TreeModel::iterator iter = _refTreeSelection->get_selected();

	if(iter) //If anything is selected
		ID = (*iter)[_columns.columnID];
	
	return ID;
}

Gtk::TreeModel::iterator TreeData::GetSelectedRowIter()
{
	Gtk::TreeModel::iterator iter = _refTreeSelection->get_selected();

	return iter;
}

Gtk::TreeModel::iterator TreeData::GetRowIterFromID(unsigned int ID)
{
	Gtk::TreeModel::iterator foundIter = _refTreeModel->children().end();
	if (_rowMap.find(ID) != _rowMap.end())
		 foundIter = _rowMap[ID];

	return foundIter;
}

// Fill TreeView in MainWindow with data
void TreeData::PopulateTreeModel()
{
	const std::map<unsigned int, DataItem> _data = _db->GetData();
	
	//Fill the TreeView's model
	for (std::map<unsigned int, DataItem>::const_iterator dataIter = _data.begin();
			dataIter != _data.end(); ++dataIter) {
		AddRow((*dataIter).second, false);
	}

	_RebuildRowMap();
}

void TreeData::PopulateRow(Gtk::TreeModel::iterator rowIter, const DataItem &ditem)
{
	Gtk::TreeModel::Row row = *rowIter;

	row[_columns.columnID] = ditem.ID;
	row[_columns.columnName] = ditem.name;
	row[_columns.columnPercentage] = ditem.percentage;
	row[_columns.columnElapsedTime] = Helpers::ParseShortTime(ditem.elapsedTime);
	row[_columns.columnGoalTime] = Helpers::ParseShortTime(ditem.goalTime);
}

void TreeData::AddRow(const DataItem &dataItem, bool rebuildRowMap)
{
	Gtk::TreeModel::iterator rowIter = _refTreeModel->append();
	Gtk::TreeModel::Row row = *rowIter;
	PopulateRow(row, dataItem);
	if (rebuildRowMap)
		_RebuildRowMap();
}

void TreeData::DeleteRow(Gtk::TreeModel::iterator rowIter)
{
	_refTreeModel->erase(rowIter);
	
	_RebuildRowMap();
}

void TreeData::UpdateRow(Gtk::TreeModel::iterator rowIter)
{
	if (rowIter == _refTreeModel->children().end())
		return;

	const DataItem ditem = _db->GetItem((*rowIter)[_columns.columnID]);
	PopulateRow(rowIter, ditem);
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

void TreeData::_RebuildRowMap()
{
	Log.Add("Rebuilding _rowMap:");
	_rowMap.clear();

	Gtk::TreeModel::Children treeChildren = _refTreeModel->children();
	for (Gtk::TreeModel::iterator treeIter = treeChildren.begin();
			treeIter != treeChildren.end(); ++treeIter)
	{
		unsigned int ID = (*treeIter)[_columns.columnID];
		_rowMap[ID] = treeIter;
		Log.Add("Found ID = " + std::to_string(ID));
	}
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
