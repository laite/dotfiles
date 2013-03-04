/*										
 * playback.h	
 * (c) Markus Klinga
 * 
 */

#ifndef PLAYBACK_H
#define PLAYBACK_H

#include "backend.h"
#include "library.h"

class Playback 
{
	public:

		explicit Playback(Library *l);

		void StartPlayback();
		void StopPlayback();

		const gint64 GetPosition() const { return sound.GetPosition(); }
		const gint64 GetLength() const { return sound.GetLength(); }

		void NextSong();

		const bool IsPlaying() const { return _playing; }

	private:

		Sound sound;
		Library *library;

		bool _playing;
		
};


#endif /* end PLAYBACK_H */
