/*										
 * widget.cpp	
 * (c) Markus Klinga
 * 
 */

#include <boost/bind.hpp>

#include "widget.h"
#include "global.h"
#include "engine.h"


InfoLabel::InfoLabel(std::string s)
	: _label(s)
{
	playback = Global::player.GetPlayback();

	// Hook to event
	Global::player.Hook(Global::EVENT::E_PLAYBACK_SECOND, boost::bind(&InfoLabel::_UpdateText, this));
}

InfoLabel::~InfoLabel()
{
	// TODO: Unhook everything
}

void InfoLabel::SetInfoText(std::string format, const Song* song)
{
	if (!song)
		song = playback->GetCurrentSong();

	// TODO: grab all non-song related items from format before sending to ->Query()
	Glib::ustring query = song->Query(format);
	gint64 cur = playback->GetPosition();
	gint64 total = playback->GetLength();
	query += " " + std::to_string(static_cast<int>(round(cur/1000000000.0))) + "/" + std::to_string(static_cast<int>(round(total/1000000000.0)));

	_label.set_text(query);
}

void InfoLabel::_UpdateText()
{
	Global::Log.Add("update!");
}

