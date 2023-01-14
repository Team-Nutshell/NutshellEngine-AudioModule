#pragma once
#include "../external/Common/module_interfaces/ntsh_audio_module_interface.h"
#include "../external/Module/utils/ntsh_module_defines.h"
#include "../external/openal-soft/include/AL/al.h"
#include "../external/openal-soft/include/AL/alc.h"
#include <unordered_map>

#define alCall(function, ...) alCallImpl(__FILE__, __LINE__, function, __VA_ARGS__)

inline bool alCheckErrors(const std::string& filename, const uint32_t line) {
	ALenum error = alGetError();
	if (error != AL_NO_ERROR) {
		switch (error) {
		case AL_INVALID_NAME:
			NTSH_MODULE_ERROR("AL Error: Name is invalid.\nFile: " + filename + "\nLine: " + std::to_string(line), NTSH_RESULT_MODULE_ERROR);
			break;
		case AL_INVALID_ENUM:
			NTSH_MODULE_ERROR("AL Error: Enum is invalid.\nFile: " + filename + "\nLine: " + std::to_string(line), NTSH_RESULT_MODULE_ERROR);
			break;
		case AL_INVALID_VALUE:
			NTSH_MODULE_ERROR("AL Error: Value is invalid.\nFile: " + filename + "\nLine: " + std::to_string(line), NTSH_RESULT_MODULE_ERROR);
			break;
		case AL_INVALID_OPERATION:
			NTSH_MODULE_ERROR("AL Error: Operation is invalid.\nFile: " + filename + "\nLine: " + std::to_string(line), NTSH_RESULT_MODULE_ERROR);
			break;
		case AL_OUT_OF_MEMORY:
			NTSH_MODULE_ERROR("AL Error: Out of memory.\nFile: " + filename + "\nLine: " + std::to_string(line), NTSH_RESULT_MODULE_ERROR);
			break;
		default:
			NTSH_MODULE_ERROR("AL Error: Unknown error.\nFile: " + filename + "\nLine: " + std::to_string(line), NTSH_RESULT_MODULE_ERROR);
			break;
		}
	}

	return true;
}

template <typename alFunction, typename... Params>
auto alCallImpl(const char* filename, const uint32_t line, alFunction function, Params... params)
->typename std::enable_if_t<!std::is_same_v<void, decltype(function(params...))>, decltype(function(params...))> {
	auto r = function(std::forward<Params>(params)...);
	alCheckErrors(filename, line);

	return r;
}

template <typename alFunction, typename... Params>
auto alCallImpl(const char* filename, const uint32_t line, alFunction function, Params... params)
->typename std::enable_if_t<std::is_same_v<void, decltype(function(params...))>, bool> {
	function(std::forward<Params>(params)...);

	return alCheckErrors(filename, line);
}

#define alcCall(function, device, ...) alcCallImpl(__FILE__, __LINE__, function, device, __VA_ARGS__)

inline bool alcCheckErrors(const std::string& filename, const uint32_t line, ALCdevice* device) {
	ALCenum error = alcGetError(device);
	if (error != ALC_NO_ERROR) {
		switch (error) {
		case ALC_INVALID_DEVICE:
			NTSH_MODULE_ERROR("ALC Error: Device is invalid.\nFile: " + filename + "\nLine: " + std::to_string(line), NTSH_RESULT_MODULE_ERROR);
			break;
		case ALC_INVALID_CONTEXT:
			NTSH_MODULE_ERROR("ALC Error: Context is invalid.\nFile: " + filename + "\nLine: " + std::to_string(line), NTSH_RESULT_MODULE_ERROR);
			break;
		case ALC_INVALID_ENUM:
			NTSH_MODULE_ERROR("ALC Error: Enum is invalid.\nFile: " + filename + "\nLine: " + std::to_string(line), NTSH_RESULT_MODULE_ERROR);
			break;
		case ALC_INVALID_VALUE:
			NTSH_MODULE_ERROR("ALC Error: Value is invalid.\nFile: " + filename + "\nLine: " + std::to_string(line), NTSH_RESULT_MODULE_ERROR);
			break;
		case ALC_OUT_OF_MEMORY:
			NTSH_MODULE_ERROR("AL Error: Out of memory.\nFile: " + filename + "\nLine: " + std::to_string(line), NTSH_RESULT_MODULE_ERROR);
			break;
		default:
			NTSH_MODULE_ERROR("ALC Error: Unknown error.\nFile: " + filename + "\nLine: " + std::to_string(line), NTSH_RESULT_MODULE_ERROR);
			break;
		}
	}

	return true;
}

template <typename alcFunction, typename... Params>
auto alcCallImpl(const char* filename, const uint32_t line, alcFunction function, ALCdevice* device, Params... params)
->typename std::enable_if_t<!std::is_same_v<void, decltype(function(params...))>, bool> {
	function(std::forward<Params>(params)...);

	return alcCheckErrors(filename, line, device);
}

template <typename alcFunction, typename ReturnType, typename... Params>
auto alcCallImpl(const char* filename, const uint32_t line, alcFunction function, ReturnType& returnValue, ALCdevice* device, Params... params)
->typename std::enable_if_t<!std::is_same_v<void, decltype(function(params...))>, bool> {
	returnValue = function(std::forward<Params>(params)...);

	return alcCheckErrors(filename, line, device);
}

struct OpenALSound {
	ALuint buffer;
	ALuint source;
	ALint state;
	float gain = 1.0f;
	float pitch = 1.0f;
};

class NutshellAudioModule : public NutshellAudioModuleInterface {
public:
	NutshellAudioModule() : NutshellAudioModuleInterface("Nutshell Audio OpenAL Soft Module") {}

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

private:
	ALCdevice* m_device = nullptr;
	ALCcontext* m_context = nullptr;

	std::unordered_map<Ntsh::SoundId, OpenALSound> m_idToSound;

	Ntsh::SoundId m_id = 0;
};