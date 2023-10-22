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

		// Plays the sound with identifier soundID at a certain gain and pitch and returns a unique identifier
		SoundSourceID playSound(SoundID soundID, float gain, float pitch);
		// Plays the sound with identifier soundID at a specific position and at a certain gain and pitch and returns a unique identifier
		SoundSourceID playSoundAtPosition(SoundID soundID, const Math::vec3& position, float gain, float pitch);
		// Pauses the sound with identifier soundSourceID
		void resumeSoundSource(SoundSourceID soundSourceID);
		// Pauses the sound with identifier soundSourceID
		void pauseSoundSource(SoundSourceID soundSourceID);
		// Stops the sound with identifier soundSourceID
		void stopSoundSource(SoundSourceID soundSourceID);

		// Returns the state of the sound source
		SoundSourceState getSoundSourceState(SoundSourceID soundSourceID);
		// Returns true if the sound with identifier soundID has any sound source currently playing, else, returns false
		bool isSoundPlaying(SoundID soundID);

		// Sets the position of the sound source with identifieer soundSourceID
		void setSoundSourcePosition(SoundSourceID soundSourceID, const Math::vec3& position);
		// Gets the position of the sound source with identifier soundSourceID
		Math::vec3 getSoundSourcePosition(SoundSourceID soundSourceID);

		// Sets the gain of the sound source with identifier soundSourceID
		void setSoundSourceGain(SoundSourceID soundSourceID, float newGain);
		// Gets the gain of the sound source with identifier soundSourceID
		float getSoundSourceGain(SoundSourceID soundSourceID);

		// Sets the pitch of the sound source with identifier soundSourceID
		void setSoundSourcePitch(SoundSourceID soundSourceID, float newPitch);
		// Gets the pitch of the sound source with identifier soundSourceID
		float getSoundSourcePitch(SoundSourceID soundSourceID);

		// Sets the entity that will listen to sounds played with playAtPosition
		void setSoundListenerEntity(Entity entity);
	};

}