/*										
 * engine.h	
 * (c) Markus Klinga
 * 
 */

#ifndef ENGINE_H
#define ENGINE_H

#include <string>
#include <map>
#include <boost/signal.hpp>

#include "playback.h"
#include "library.h"
#include "global.h"

class Event 
{
	public:

		Event(Global::EVENT e);

		Event(const Event &rhs);

		boost::signals::connection Connect(boost::signal<void ()>::slot_function_type cb_type);
		void Disconnect(const boost::signals::connection&);

	private:

		boost::signal<void ()> _signal;

		Global::EVENT _event;
};

class EventHandler 
{
	public:

		typedef boost::signal<void ()>::slot_function_type cb_type;

		EventHandler();

		boost::signals::connection AddHook(Global::EVENT, cb_type cb);
		bool RemoveHook(const Global::EVENT, const boost::signals::connection&);

	private:

		std::map< Global::EVENT, Event > _events;
};

class Engine 
{
	typedef std::vector<Playlist*>::size_type playlist_index;
	typedef boost::signal<void ()>::slot_function_type cb_type;

	public:

		Engine();

		Playback *GetPlayback() { return &playback; }
		Library  *GetLibrary() { return &library; }

		Playlist *GetCurrentPlaylist() { return _playlists[_currentPlaylist]; }

		// there is no boundary checking here
		Playlist *GetPlaylist(playlist_index index) { return _playlists[index]; }

		boost::signals::connection Hook(Global::EVENT e, cb_type cb) { return _eventHandler.AddHook(e, cb); }
		bool Unhook(const Global::EVENT e, const boost::signals::connection &con) { return _eventHandler.RemoveHook(e, con); }

	private:

		// the main library of player
		Library library;

		// the main playback interface
		Playback playback;

		// all playlists
		std::vector<Playlist*> _playlists;

		// index of currently active playlist
		playlist_index _currentPlaylist;
		
		EventHandler _eventHandler;
};

#endif /* end ENGINE_H */
