#pragma once
#include "../Common/modules/ntshengn_audio_module_interface.h"
#include "../Module/utils/ntshengn_module_defines.h"
#include "../external/openal-soft/include/AL/al.h"
#include "../external/openal-soft/include/AL/alc.h"
#include "../external/openal-soft/include/AL/alext.h"
#include <vector>
#include <unordered_map>

#define alCall(function, ...) alCallImpl(std::filesystem::path(__FILE__).filename().string().c_str(), __LINE__, function, __VA_ARGS__)

inline bool alCheckErrors(const std::string& filename, const uint32_t line) {
	NTSHENGN_UNUSED(filename);
	NTSHENGN_UNUSED(line);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR) {
		switch (error) {
		case AL_INVALID_NAME:
			NTSHENGN_MODULE_ERROR("AL Error: Name is invalid.\nFile: " + filename + "\nLine: " + std::to_string(line));
			break;
		case AL_INVALID_ENUM:
			NTSHENGN_MODULE_ERROR("AL Error: Enum is invalid.\nFile: " + filename + "\nLine: " + std::to_string(line));
			break;
		case AL_INVALID_VALUE:
			NTSHENGN_MODULE_ERROR("AL Error: Value is invalid.\nFile: " + filename + "\nLine: " + std::to_string(line));
			break;
		case AL_INVALID_OPERATION:
			NTSHENGN_MODULE_ERROR("AL Error: Operation is invalid.\nFile: " + filename + "\nLine: " + std::to_string(line));
			break;
		case AL_OUT_OF_MEMORY:
			NTSHENGN_MODULE_ERROR("AL Error: Out of memory.\nFile: " + filename + "\nLine: " + std::to_string(line));
			break;
		default:
			NTSHENGN_MODULE_ERROR("AL Error: Unknown error.\nFile: " + filename + "\nLine: " + std::to_string(line));
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
			NTSHENGN_MODULE_ERROR("ALC Error: Device is invalid.\nFile: " + filename + "\nLine: " + std::to_string(line));
			break;
		case ALC_INVALID_CONTEXT:
			NTSHENGN_MODULE_ERROR("ALC Error: Context is invalid.\nFile: " + filename + "\nLine: " + std::to_string(line));
			break;
		case ALC_INVALID_ENUM:
			NTSHENGN_MODULE_ERROR("ALC Error: Enum is invalid.\nFile: " + filename + "\nLine: " + std::to_string(line));
			break;
		case ALC_INVALID_VALUE:
			NTSHENGN_MODULE_ERROR("ALC Error: Value is invalid.\nFile: " + filename + "\nLine: " + std::to_string(line));
			break;
		case ALC_OUT_OF_MEMORY:
			NTSHENGN_MODULE_ERROR("AL Error: Out of memory.\nFile: " + filename + "\nLine: " + std::to_string(line));
			break;
		default:
			NTSHENGN_MODULE_ERROR("ALC Error: Unknown error.\nFile: " + filename + "\nLine: " + std::to_string(line));
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

struct OpenALSoundSource {
	NtshEngn::SoundID soundID;
	ALuint source;
	ALint state;
	NtshEngn::Math::vec3 position;
	float gain = 1.0f;
	float pitch = 1.0f;
	bool looping = false;
};

struct OpenALSound {
	ALuint buffer;
	float length;
	std::set<NtshEngn::SoundSourceID> soundSourceIDs;
};

namespace NtshEngn {

	class AudioModule : public AudioModuleInterface {
	public:
		AudioModule() : AudioModuleInterface("NutshellEngine OpenAL Soft Audio Module") {}

		void init();
		void update(float dt);
		void destroy();

		// Loads the sound described in the sound parameter in the internal format and returns a unique identifier
		SoundID load(const Sound& sound);

		// Plays the sound with identifier soundID at a certain gain and pitch, looping or not, and returns a unique identifier
		SoundSourceID playSound(SoundID soundID, float gain, float pitch, bool looping, float startTime);
		// Plays the sound with identifier soundID at a specific position and at a certain gain and pitch, looping or not, at a start time, and returns a unique identifier
		SoundSourceID playSoundAtPosition(SoundID soundID, const Math::vec3& position, float gain, float pitch, bool looping, float startTime);
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

		// Sets the current time of a sound source, in seconds
		void setSoundSourceTime(SoundSourceID soundSourceID, float newTime);
		// Returns the current time of a sound source, in seconds
		float getSoundSourceTime(SoundSourceID soundSourceID);

		// Sets the position of the sound source with identifieer soundSourceID
		void setSoundSourcePosition(SoundSourceID soundSourceID, const Math::vec3& newPosition);
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

		// If the looping parameter is true, makes the sound source with identifier soundSourceID looping, else, makes the sound source with identifier soundSourceID not looping
		void setSoundSourceLooping(SoundSourceID soundSourceID, bool looping);
		// Returns true if the sound source with identifier soundSourceID is looping, else, returns false
		bool isSoundSourceLooping(SoundSourceID soundSourceID);

		// Sets the master gain
		void setMasterGain(float newGain);
		// Returns the master gain
		float getMasterGain();

	public:
		const ComponentMask getComponentMask() const;

		void onEntityComponentAdded(Entity entity, Component componentID);
		void onEntityComponentRemoved(Entity entity, Component componentID);
		
	public:
		bool reopenDevice = false;

	private:
		ALCdevice* m_device = nullptr;
		ALCcontext* m_context = nullptr;

		std::unordered_map<SoundID, OpenALSound> m_soundIDToSound;
		std::unordered_map<SoundSourceID, OpenALSoundSource> m_soundSourceIDToSoundSource;

		SoundID m_soundID = 0;
		SoundID m_soundSourceID = 0;

		std::unordered_map<const Sound*, SoundID> m_soundAddresses;

		LPALCEVENTCONTROLSOFT m_alcEventControlSOFT;
		LPALCEVENTCALLBACKSOFT m_alcEventCallbackSOFT;
		LPALCREOPENDEVICESOFT m_alcReopenDeviceSOFT;

		Entity m_listenerEntity = NTSHENGN_ENTITY_UNKNOWN;
	};

}

void ALC_APIENTRY systemEventCallback(ALCenum eventType, ALCenum deviceType, ALCdevice* device, ALCsizei length, const ALCchar* message, void* userParam) noexcept {
	NTSHENGN_UNUSED(device);
	NTSHENGN_UNUSED(length);
	NTSHENGN_UNUSED(message);

	if ((eventType == ALC_EVENT_TYPE_DEFAULT_DEVICE_CHANGED_SOFT) && (deviceType == ALC_PLAYBACK_DEVICE_SOFT)) {
		static_cast<NtshEngn::AudioModule*>(userParam)->reopenDevice = true;
	}
}