/*										
 * main.cpp	
 * (c) Markus Klinga
 * Mail-handling example (ex. 13.16-13.19)
 */

#include "Message.h"
#include "Folder.h"

int main()
{
	std::cout << std::endl << "#####  Init Mail-handling example  #####" << std::endl << std::endl;
	// Init: create few different messages and two folders
	Message testMessage("Reaction","this has been fun.");
	Message emptyMessage; // emptyMessage gets <No title> and <No contents> for its attributes
	Message fullMessage("Awful!", "Just awful.");
	Folder sent("Sent items"), draft("Draft");

	// add messages individually to folder 'sent'
	sent.AddMessage(&testMessage);
	sent.AddMessage(&emptyMessage);
	sent.AddMessage(&fullMessage);

	std::cout << std::endl << "#####  1st PrintOut  #####" << std::endl << std::endl;
	sent.PrintContents();
	draft.PrintContents(); // there isn't anything in draft just yet

	// copy sent - folder to draft, remove empty message and print out
	draft = sent;
	draft.RemoveMessage(&emptyMessage);
	draft.PrintContents();

	// create a new folder through copy construct from draft
	Folder compromise = draft;

	// note! this creates new message newTest AND copies it to every folder where testMessage is 
	// it seems 'duplicate', but there's a different real item behind it
	Message newTest = emptyMessage;

	// remove test message from folder compromise (titled 'draft (copy)' in program)
	compromise.RemoveMessage(&testMessage);
	// since compromise is copied from draft, it has no emptyMessage and thus newTest doesn't appear there unless we manually add it
	compromise.AddMessage(&newTest);

	std::cout << std::endl << "#####  2nd PrintOut  #####" << std::endl << std::endl;
	sent.PrintContents();
	draft.PrintContents();
	compromise.PrintContents();

	std::cout << std::endl << "#####  Close down Mail-handling example  #####" << std::endl << std::endl;
	// program still prints out some item removing messages when quitting

	return 0;
}
