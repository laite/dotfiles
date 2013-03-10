/*										
 * engine.cpp	
 * (c) Markus Klinga
 * 
 */

#include "engine.h"

Engine::Engine()
	: _currentPlaylist(0)
{
	if (!_playlists.size())
		_playlists.push_back(new Playlist);

	// TODO: save active playlist index on exit, restore here
	playback.SetActivePlaylist(_playlists.at(_currentPlaylist));
}


/*
 *  Event
 */


Event::Event(Global::EVENT e)
{
	_event = e; 
}

Event::Event(const Event &rhs)
{
	// we cannot copy _signal due to its nature
	_event = rhs._event;
}

boost::signals::connection Event::Connect(boost::signal<void ()>::slot_function_type cb_type)
{
	return _signal.connect(cb_type);
}

void Event::Disconnect(const boost::signals::connection &connection)
{
	_signal.disconnect(connection);
}

void Event::Trigger()
{
	_signal();
}


/*
 *  EventHandler
 */


EventHandler::EventHandler()
{
	// Create events of everything in Global::EVENT
	for (int i = 0; i != Global::EVENT::E_LAST; ++i)
		_events.insert(std::make_pair(static_cast<Global::EVENT>(i), Event(static_cast<Global::EVENT>(i))));
}

boost::signals::connection EventHandler::AddHook(Global::EVENT e, EventHandler::cb_type cb)
{
	/*
	 *  we return empty (disconnected) connection if
	 *  event is not found in map (this _really_ shouldn't happen) 
	 */
	if (_events.find(e) == _events.end())
		return boost::signals::connection();

	return _events.at(e).Connect(cb);
}

bool EventHandler::RemoveHook(const Global::EVENT e, const boost::signals::connection &connectionID)
{
	if (_events.find(e) == _events.end())
		return false;

	_events.at(e).Disconnect(connectionID);
	return true;
}

void EventHandler::Trigger(Global::EVENT e)
{
	if (_events.find(e) == _events.end())
		return;

	_events.at(e).Trigger();
}
