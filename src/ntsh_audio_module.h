#pragma once
#include "../external/Common/module_interfaces/ntsh_audio_module_interface.h"

class NutshellAudioModule : public NutshellAudioModuleInterface {
public:
	NutshellAudioModule() : NutshellAudioModuleInterface("Nutshell Audio Test Module") {}

	void init();
	void update(double dt);
	void destroy();

	// Loads the sound described in the audio parameter in the internal format and returns a unique identifier
	Ntsh::SoundId load(const Ntsh::Sound audio);

	// Plays the sound with identifier soundId
	void play(Ntsh::SoundId audioId);
	// Pauses the sound with identifier soundId
	void pause(Ntsh::SoundId audioId);
	// Stops the sound with identifier soundId
	void stop(Ntsh::SoundId audioId);

	// Returns true if the sound with identifier soundId is currently playing, else, returns false
	bool isPlaying(Ntsh::SoundId audioId);

	// Sets the gain of the sound with identifier soundId
	void setGain(Ntsh::SoundId audioId, float newGain);
	// Gets the gain of the sound with identifier soundId
	float getGain(Ntsh::SoundId audioId);

	// Sets the pitch of the sound with identifier soundId
	void setPitch(Ntsh::SoundId audioId, float newPitch);
	// Gets the pitch of the sound with identifier soundId
	float getPitch(Ntsh::SoundId audioId);
};