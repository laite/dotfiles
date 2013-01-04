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

#include <chrono>

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
	_treeView->append_column("Total", Columns().columnElapsed);
	_treeView->append_column("Avg.", Columns().columnAverage);
	_treeView->append_column("Goal", Columns().columnGoal);

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

void TreeData::PopulateRow(Gtk::TreeModel::iterator rowIter, const DataItem &dataItem)
{
	Gtk::TreeModel::Row row = *rowIter;

	row[_columns.columnID] = dataItem.ID;
	row[_columns.columnName] = dataItem.name;
	row[_columns.columnPercentage] = dataItem.percentage;

	std::chrono::duration<double,std::ratio<60*60*24> > timeAgo = std::chrono::duration_cast< std::chrono::duration<double,std::ratio<60*60*24> > >(std::chrono::steady_clock::now() - dataItem.firstRunTime);
	double hasBeen = timeAgo.count(); // this is in days

	if (Global::Config.GetAppOptions().noFunnyAverages)
		hasBeen = std::max(hasBeen, static_cast<double>(dataItem.GetSecondsFromTimeFrame()/(24*60*60)));

	if (dataItem.continuous)
	{
		row[_columns.columnElapsed] = Helpers::ParseShortTime(dataItem.elapsedTime);
		long average = (dataItem.elapsedTime/hasBeen); // we get seconds per day
		average *= (1.0*dataItem.GetSecondsFromTimeFrame()/(24*60*60)); // adapt to timeframe
		row[_columns.columnAverage] = Helpers::ParseShortTime(average);
	
		row[_columns.columnGoal] = Helpers::ParseShortTime(dataItem.goal);
	}
	else // dataItem !continuous
	{
		row[_columns.columnElapsed] = std::to_string(dataItem.GetTimes());
		double average = (dataItem.GetTimes()/(hasBeen)); // we get instances per day
		average *= (1.0*dataItem.GetSecondsFromTimeFrame()/(24*60*60));
		row[_columns.columnAverage] = Helpers::TruncateToString(average);
		row[_columns.columnGoal] = std::to_string(dataItem.goal);
	}
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
	Global::Log.Add("Rebuilding _rowMap:");
	_rowMap.clear();

	Gtk::TreeModel::Children treeChildren = _refTreeModel->children();
	for (Gtk::TreeModel::iterator treeIter = treeChildren.begin();
			treeIter != treeChildren.end(); ++treeIter)
	{
		unsigned int ID = (*treeIter)[_columns.columnID];
		_rowMap[ID] = treeIter;
		Global::Log.Add("Found ID = " + std::to_string(ID));
	}
}


/*
 *  ModelColumns
 */

ModelColumns::ModelColumns()
{
	add(columnID);
	add(columnName);
	add(columnElapsed);
	add(columnAverage);
	add(columnGoal);
	add(columnPercentage);
}
