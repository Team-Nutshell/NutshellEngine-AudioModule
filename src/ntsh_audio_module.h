#pragma once
#include "../external/Common/module_interfaces/ntsh_audio_module_interface.h"

class NutshellAudioModule : public NutshellAudioModuleInterface {
public:
	NutshellAudioModule() : NutshellAudioModuleInterface("Nutshell Audio Test Module") {}

	void init();
	void update(double dt);
	void destroy();

	// Plays an audio and returns an identifier
	NtshAudioId play(const NtshAudio& audio);
	// Pauses the audio with identifier audioId
	void pause(NtshAudioId audioId);
	// Stops the audio with identifier audioId
	void stop(NtshAudioId audioId);

	// Returns true if the audio with identifier audioId is currently playing, else, returns false
	bool isPlaying(NtshAudioId audioId);

	// Sets the gain of the audio with identifier audioId
	void setGain(NtshAudioId audioId, float newGain);
	// Gets the gain of the audio with identifier audioId
	float getGain(NtshAudioId audioId);

	// Sets the pitch of the audio with identifier audioId
	void setPitch(NtshAudioId audioId, float newPitch);
	// Gets the pitch of the audio with identifier audioId
	float getPitch(NtshAudioId audioId);
};