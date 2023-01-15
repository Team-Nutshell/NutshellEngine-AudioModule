#pragma once
#include "../external/Common/module_interfaces/ntshengn_audio_module_interface.h"

namespace NtshEngn {

	class AudioModule : public AudioModuleInterface {
	public:
		AudioModule() : AudioModuleInterface("NutshellEngine Audio Test Module") {}

		void init();
		void update(double dt);
		void destroy();

		// Loads the sound described in the sound parameter in the internal format and returns a unique identifier
		SoundId load(const Sound sound);

		// Plays the sound with identifier soundId
		void play(SoundId soundId);
		// Pauses the sound with identifier soundId
		void pause(SoundId soundId);
		// Stops the sound with identifier soundId
		void stop(SoundId soundId);

		// Returns true if the sound with identifier soundId is currently playing, else, returns false
		bool isPlaying(SoundId soundId);

		// Sets the gain of the sound with identifier soundId
		void setGain(SoundId soundId, float newGain);
		// Gets the gain of the sound with identifier soundId
		float getGain(SoundId soundId);

		// Sets the pitch of the sound with identifier soundId
		void setPitch(SoundId soundId, float newPitch);
		// Gets the pitch of the sound with identifier soundId
		float getPitch(SoundId soundId);
	};

}