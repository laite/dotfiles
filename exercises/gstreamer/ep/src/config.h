/*										
 * config.h	
 * (c) Markus Klinga
 * 
 */

#ifndef CONFIG_H
#define CONFIG_H

#include <string>

struct AppOptions
{
	// repeat mode
	enum { REPEAT_NONE, REPEAT_ONE, REPEAT_ALL };
	int repeatMode;

	// do playback buttons have labels
	bool playbackButtonLabels;

	// does cursor on active playlist choose next song
	bool playbackFollowsCursor;
};

class Options 
{
	public:

		Options();
		~Options();

		// reads saved options from file to _appOptions
		// if no parameter is given, reads default config file
		void LoadOptions(std::string file = "");

		// writes current _appOptions to file
		// if no parameter is given, writes to default config file
		void SaveOptions(std::string file = "");

		// used for getting option value around the program
		const AppOptions& GetAppOptions() const { return _appOptions; }

		// used to change option value
		AppOptions& SetAppOptions() { return _appOptions; }

		// returns $HOME/.config/laite/ep OR . (if no environment value $HOME is found)
		std::string GetSettingsFolder();
		
	private:

		AppOptions _appOptions;
};


#endif /* end CONFIG_H */
