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
	friend class Songlist;

	public:

		Song(Glib::ustring);

		const std::string GetUri() const { return uri; }

		const unsigned int GetTrack() const { return _track; }
		const Glib::ustring GetArtist() const { return _artist; }
		const Glib::ustring GetAlbum() const { return _album; }
		const Glib::ustring GetTitle() const { return _title; }

		const unsigned GetSongID() const { return _ID; }

		const Glib::ustring Query(Glib::ustring) const;


	private:

		Glib::ustring uri;
		unsigned int _track;
		Glib::ustring _artist;
		Glib::ustring _album;
		Glib::ustring _title;

		unsigned _ID;

		void _SetID(unsigned newID) { _ID = newID; }
};


#endif /* end SONG_H */
