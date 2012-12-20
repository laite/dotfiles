/*										
 * Message.h	
 * (c) Markus Klinga
 * 
 */

#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <set>

// Use forward declaration to tell about Folder class
class Folder;

class Message
{
	friend class Folder;

	public:

		Message(const std::string &title = "<No title>", const std::string &contents = "<No contents>");
		Message(const Message&);
		Message& operator=(const Message&);
		~Message();

		std::string GetTitle();
		std::string GetContents();

	private:

		/* Private variables */

		std::string _title;
		std::string _contents;
		std::set<Folder*> _folders;
		

		/* utility functions */
		
		void _AddFolder(Folder*); 		// Add folder to Message
		void _RemoveFolder(Folder*); 	// Remove folder from Message

		// Add this Message to the Folders pointed by the parameter
		void _PutMessageInFolders(const std::set<Folder*>&);
		// Remove Message from every Folder in _folders
		void _RemoveMessageFromFolders();
};


#endif /* end of include guard: MESSAGE_H */
