#pragma once
#include "../Common/module_interfaces/ntshengn_audio_module_interface.h"
#include "../Module/utils/ntshengn_module_defines.h"
#include "../external/openal-soft/include/AL/al.h"
#include "../external/openal-soft/include/AL/alc.h"
#include <unordered_map>

#define alCall(function, ...) alCallImpl(__FILE__, __LINE__, function, __VA_ARGS__)

inline bool alCheckErrors(const std::string& filename, const uint32_t line) {
	NTSHENGN_UNUSED(filename);
	NTSHENGN_UNUSED(line);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR) {
		switch (error) {
		case AL_INVALID_NAME:
			NTSHENGN_MODULE_ERROR("AL Error: Name is invalid.\nFile: " + filename + "\nLine: " + std::to_string(line), NtshEngn::Result::ModuleError);
			break;
		case AL_INVALID_ENUM:
			NTSHENGN_MODULE_ERROR("AL Error: Enum is invalid.\nFile: " + filename + "\nLine: " + std::to_string(line), NtshEngn::Result::ModuleError);
			break;
		case AL_INVALID_VALUE:
			NTSHENGN_MODULE_ERROR("AL Error: Value is invalid.\nFile: " + filename + "\nLine: " + std::to_string(line), NtshEngn::Result::ModuleError);
			break;
		case AL_INVALID_OPERATION:
			NTSHENGN_MODULE_ERROR("AL Error: Operation is invalid.\nFile: " + filename + "\nLine: " + std::to_string(line), NtshEngn::Result::ModuleError);
			break;
		case AL_OUT_OF_MEMORY:
			NTSHENGN_MODULE_ERROR("AL Error: Out of memory.\nFile: " + filename + "\nLine: " + std::to_string(line), NtshEngn::Result::ModuleError);
			break;
		default:
			NTSHENGN_MODULE_ERROR("AL Error: Unknown error.\nFile: " + filename + "\nLine: " + std::to_string(line), NtshEngn::Result::ModuleError);
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
	NTSHENGN_UNUSED(filename);
	NTSHENGN_UNUSED(line);
	ALCenum error = alcGetError(device);
	if (error != ALC_NO_ERROR) {
		switch (error) {
		case ALC_INVALID_DEVICE:
			NTSHENGN_MODULE_ERROR("ALC Error: Device is invalid.\nFile: " + filename + "\nLine: " + std::to_string(line), NtshEngn::Result::ModuleError);
			break;
		case ALC_INVALID_CONTEXT:
			NTSHENGN_MODULE_ERROR("ALC Error: Context is invalid.\nFile: " + filename + "\nLine: " + std::to_string(line), NtshEngn::Result::ModuleError);
			break;
		case ALC_INVALID_ENUM:
			NTSHENGN_MODULE_ERROR("ALC Error: Enum is invalid.\nFile: " + filename + "\nLine: " + std::to_string(line), NtshEngn::Result::ModuleError);
			break;
		case ALC_INVALID_VALUE:
			NTSHENGN_MODULE_ERROR("ALC Error: Value is invalid.\nFile: " + filename + "\nLine: " + std::to_string(line), NtshEngn::Result::ModuleError);
			break;
		case ALC_OUT_OF_MEMORY:
			NTSHENGN_MODULE_ERROR("AL Error: Out of memory.\nFile: " + filename + "\nLine: " + std::to_string(line), NtshEngn::Result::ModuleError);
			break;
		default:
			NTSHENGN_MODULE_ERROR("ALC Error: Unknown error.\nFile: " + filename + "\nLine: " + std::to_string(line), NtshEngn::Result::ModuleError);
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

namespace NtshEngn {

	class AudioModule : public AudioModuleInterface {
	public:
		AudioModule() : AudioModuleInterface("NutshellEngine OpenAL Soft Audio Module") {}

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

	private:
		ALCdevice* m_device = nullptr;
		ALCcontext* m_context = nullptr;

		std::unordered_map<SoundID, OpenALSound> m_idToSound;

		SoundID m_id = 0;
	};

}