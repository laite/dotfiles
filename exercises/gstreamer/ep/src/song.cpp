/*										
 * song.cpp	
 * (c) Markus Klinga
 * 
 */

#include "song.h"
#include "global.h"

Song::Song(Glib::ustring address)
	: uri(address)
{
	TagLib::FileRef file(uri.c_str());
	if (!file.isNull() && file.tag())
	{
		// TODO: Make sure values are properly formatted Glib::ustring (utf-8)
		TagLib::Tag *tag = file.tag();
		_track = tag->track();
		_artist = tag->artist().to8Bit();
		_album = tag->album().to8Bit();
		_title = tag->title().to8Bit();
	}
	else
		Global::Log.Add("No tag found! " + uri);
}

const Glib::ustring Song::Query(Glib::ustring querytext) const
{
	Glib::ustring result("");
	Glib::ustring::iterator character;
	bool hasFirst = false;

	for (character = querytext.begin(); character != querytext.end(); ++character)
	{
		if ((*character == '%') || (hasFirst))
		{
			if (hasFirst)
			{
				hasFirst = false;
				if (*character == 'a')
					result += _artist;
				else if (*character == 'l')
					result += _album;
				else if (*character == 't')
					result += _title;
				else if (*character == 'n')
					result += std::to_string(_track);
				else
					result += '%' + *character;
			}
			else
				hasFirst = true;
		}
		else
			result += *character;
	}

	return result;
}
