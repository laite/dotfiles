/*										
 * Folder.cpp	
 * (c) Markus Klinga
 * 
 */

#include "Folder.h"
#include "Message.h"

// init static variable here
int Folder::amountOfFolders(0);

Folder::Folder(const std::string title):
	_title(title),
	amountOfMessages(0)
{
	++Folder::amountOfFolders;
	std::cout << "Folder \"" << _title << "\" constructed (Total: " << amountOfFolders << ")" << std::endl;
}

Folder::~Folder()
{
	std::cout << "* Starting Folder destruction (" << _messages.size() << " items)" << std::endl;
	_RemoveFolderFromMessages();
	--Folder::amountOfFolders;
	std::cout << "Folder destroyed" << std::endl;
}

Folder::Folder(const Folder &rhsFolder):
	_messages(rhsFolder._messages),
	amountOfMessages(rhsFolder.amountOfMessages)
{
	std::string copyName = rhsFolder._title + " (copy)";
	_title = copyName;
	// when copy constructing folder, we need to copy all message pointers
	_PutFolderToMessages();
	++Folder::amountOfFolders;
	std::cout << "Folder \"" << _title << "\" COPY constructed (Total: " << amountOfFolders << ")" << std::endl;
}

Folder& Folder::operator=(const Folder &rhsFolder)
{
	_RemoveFolderFromMessages(); // clean lhs folder from all the message's data

	amountOfMessages = rhsFolder.amountOfMessages;
	_messages = rhsFolder._messages; // copy rhs messages in place

	_PutFolderToMessages(); // and update all the messages correspondingly
	std::cout << "Folder assigned with " << amountOfMessages << " messages" << std::endl;
}

void Folder::AddMessage(Message *message)
{
	std::pair<std::set<Message*>::iterator,bool> returnValue = _messages.insert(message);
	if (returnValue.second)
	{
		++amountOfMessages;
		message->_AddFolder(this);
		std::cout << "Added message \"" << message->GetTitle() << "\" to " << _title << std::endl;
	}
}

void Folder::RemoveMessage(Message *message)
{
	// return value is the number of erased items (here either zero or one)
	std::set<Message*>::size_type returnValue = _messages.erase(message);
	if (returnValue)
	{
		--amountOfMessages;
		message->_RemoveFolder(this);
		std::cout << "Removed Message \"" << message->GetTitle() << "\" from Folder " << _title << " (" << amountOfMessages << " items left)" << std::endl;
	}
}

void Folder::_PutFolderToMessages()
{
	for (std::set<Message*>::const_iterator messageIter = _messages.begin();
			messageIter != _messages.end(); ++messageIter)
	{
		(*messageIter)->_AddFolder(this);
	}
}

void Folder::_RemoveFolderFromMessages()
{
	for (std::set<Message*>::const_iterator messageIter = _messages.begin();
			messageIter != _messages.end(); ++messageIter)
	{
		(*messageIter)->_RemoveFolder(this);
	}
}

void Folder::PrintContents()
{
	int counter = 0;
	for (std::set<Message*>::const_iterator messageIter = _messages.begin();
			messageIter != _messages.end(); ++messageIter)
	{
		if (counter == 0)
			std::cout << ">> Folder \"" << _title << "\" has following messages:" << std::endl;
		std::cout << "\t[" << ++counter << "/" << amountOfMessages << "] " << (*messageIter)->GetTitle() << ": " << (*messageIter)->GetContents() << std::endl;

	}

	if (counter == 0)
	{
		std::cout << ">> Folder \"" << _title << "\" has no messages" << std::endl;
	}
}
