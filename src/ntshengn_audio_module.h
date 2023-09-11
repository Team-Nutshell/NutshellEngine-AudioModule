#pragma once
#include "../Common/module_interfaces/ntshengn_audio_module_interface.h"

namespace NtshEngn {

	class AudioModule : public AudioModuleInterface {
	public:
		AudioModule() : AudioModuleInterface("NutshellEngine Default Audio Module") {}

		void init();
		void update(double dt);
		void destroy();

		// Loads the sound described in the sound parameter in the internal format and returns a unique identifier
		SoundID load(const Sound& sound);

		// Plays the sound with identifier soundID, if the sound is paused, it is resumed
		void play(SoundID soundID);
		// Pauses the sound with identifier soundID
		void pause(SoundID soundID);
		// Stops the sound with identifier soundID
		void stop(SoundID soundID);

		// Returns true if the sound with identifier soundID is currently playing, else, returns false
		bool isPlaying(SoundID soundID);

		// Sets the gain of the sound with identifier soundID
		void setGain(SoundID soundID, float newGain);
		// Gets the gain of the sound with identifier soundID
		float getGain(SoundID soundID);

		// Sets the pitch of the sound with identifier soundID
		void setPitch(SoundID soundID, float newPitch);
		// Gets the pitch of the sound with identifier soundID
		float getPitch(SoundID soundID);
	};

}