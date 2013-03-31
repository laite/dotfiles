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

class Song 
{
	public:

		Song(Glib::ustring);

		const std::string GetUri() const { return uri; }

		const unsigned int GetTrack() const { return _track; }
		const std::string GetArtist() const { return _artist; }
		const std::string GetAlbum() const { return _album; }
		const std::string GetTitle() const { return _title; }

		const std::string Query(Glib::ustring) const;


	private:

		std::string uri;
		unsigned int _track;
		std::string _artist;
		std::string _album;
		std::string _title;
};


#endif /* end SONG_H */
