/*										* Message.cpp	
 * (c) Markus Klinga
 * 
 */

#include <iostream>

#include "Message.h"
#include "Folder.h"

Message::Message(const std::string &title, const std::string &contents):
	_title(title),
	_contents(contents)
{
	std::cout << "Message \"" << _title << "\" constructed" << std::endl;
}

Message::Message(const Message &sourceMessage): 
	_title(sourceMessage._title),
	_contents(sourceMessage._contents),
	_folders(sourceMessage._folders)
{
	_PutMessageInFolders(_folders);

}

Message& Message::operator=(const Message &rhsMessage)
{
	// we mustn't do any assignments if both sides are already the same!
	if (&rhsMessage != this)
	{
		// first we 'empty' all current folder bindings
		_RemoveMessageFromFolders();

		// then assign new values
		_title = rhsMessage._title;
		_contents = rhsMessage._contents;
		_folders = rhsMessage._folders;

		// and add this message to all folders where rhsMessage is
		_PutMessageInFolders(rhsMessage._folders);
	}

	return *this;
}

Message::~Message()
{
	std::cout << "Message " << _title << " destroyed" << std::endl;
	_RemoveMessageFromFolders();
}

// Put a pointer to message in all folders where it belongs
void Message::_PutMessageInFolders(const std::set<Folder*> &folderSet)
{
	std::cout << "* Putting message " << _title << " to " << folderSet.size() << " folders." << std::endl;
	for (std::set<Folder*>::const_iterator folderIter = folderSet.begin(); 
				folderIter != folderSet.end(); 
				++folderIter)
	{
		(*folderIter)->AddMessage(this);
	}
}

// Remove Message from all folders
void Message::_RemoveMessageFromFolders()
{
	for (std::set<Folder*>::const_iterator folderIter = _folders.begin(); 
				folderIter != _folders.end(); 
				++folderIter)
	{
		(*folderIter)->RemoveMessage(this);
	}

}

void Message::_AddFolder(Folder *newFolder)
{
	std::pair<std::set<Folder*>::iterator,bool> returnValue = _folders.insert(newFolder);
	if (returnValue.second)
		newFolder->AddMessage(this);
}

void Message::_RemoveFolder(Folder *exFolder)
{
	std::set<Folder*>::size_type returnValue = _folders.erase(exFolder);
	if (returnValue)
	{
		exFolder->RemoveMessage(this);
		if (_folders.size())
			std::cout << "Message \"" << _title << "\" is still in " << _folders.size() << " folders." << std::endl;
	}
}

std::string Message::GetTitle()
{
	return _title;
}

std::string Message::GetContents()
{
	return _contents;
}
