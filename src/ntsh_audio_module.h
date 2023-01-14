#pragma once
#include "../external/Common/module_interfaces/ntsh_audio_module_interface.h"

class NutshellAudioModule : public NutshellAudioModuleInterface {
public:
	NutshellAudioModule() : NutshellAudioModuleInterface("Nutshell Audio Test Module") {}

	void init();
	void update(double dt);
	void destroy();

	// Loads the sound described in the sound parameter in the internal format and returns a unique identifier
	Ntsh::SoundId load(const Ntsh::Sound sound);

	// Plays the sound with identifier soundId
	void play(Ntsh::SoundId soundId);
	// Pauses the sound with identifier soundId
	void pause(Ntsh::SoundId soundId);
	// Stops the sound with identifier soundId
	void stop(Ntsh::SoundId soundId);

	// Returns true if the sound with identifier soundId is currently playing, else, returns false
	bool isPlaying(Ntsh::SoundId soundId);

	// Sets the gain of the sound with identifier soundId
	void setGain(Ntsh::SoundId soundId, float newGain);
	// Gets the gain of the sound with identifier soundId
	float getGain(Ntsh::SoundId soundId);

	// Sets the pitch of the sound with identifier soundId
	void setPitch(Ntsh::SoundId soundId, float newPitch);
	// Gets the pitch of the sound with identifier soundId
	float getPitch(Ntsh::SoundId soundId);
};