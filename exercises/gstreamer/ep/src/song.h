/*										
 * song.h	
 * (c) Markus Klinga
 * 
 */

#ifndef SONG_H
#define SONG_H

#include <gtkmm.h>
#include <fileref.h>
#include <tag.h>

#include "global.h"

class Song 
{
	public:

		Song(Glib::ustring);

		const std::string GetUri() const { return uri; }

		const std::string Query(Glib::ustring) const;

	private:

		std::string uri;
		std::string _artist;
		std::string _album;
		std::string _title;
};


#endif /* end SONG_H */
