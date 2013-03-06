/*										
 * song.cpp	
 * (c) Markus Klinga
 * 
 */

#include "song.h"

Song::Song(Glib::ustring address)
	: uri(address)
{
	TagLib::FileRef file(uri.c_str());
	if (!file.isNull() && file.tag())
	{
		TagLib::Tag *tag = file.tag();
		_artist = tag->artist().to8Bit();
		_album = tag->album().to8Bit();
		_title = tag->title().to8Bit();
	}
	else
		std::cout << "No tag found! " << uri << std::endl;
}

const std::string Song::Query(Glib::ustring querytext) const
{
	return (_title + " by " + _artist);

}
