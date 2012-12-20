/*										
 * Folder.h	
 * (c) Markus Klinga
 * 
 */

#ifndef FOLDER_H
#define FOLDER_H

#include <set>
#include <string>
#include <iostream>


class Message;

class Folder
{

	public:

		Folder(const std::string title="");
		Folder(const Folder&);
		Folder& operator=(const Folder&);
		~Folder();
		
		// Add/remove Message to/from this folder
		void AddMessage(Message*);
		void RemoveMessage(Message*);

		// cout the messages in this folder
		void PrintContents();

		// public variables
		int amountOfMessages;
		static int amountOfFolders;

	private:

		std::string _title;
		std::set<Message*> _messages;

		// Put this folder on all messages' _folders variable
		void _PutFolderToMessages();
		// Remove this folder from all messages
		void _RemoveFolderFromMessages();
};

#endif /* end FOLDER_H */
