#include "ntshengn_audio_module.h"
#include "../Module/utils/ntshengn_dynamic_library.h"
#include "../Common/utils/ntshengn_defines.h"
#include "../Common/utils/ntshengn_enums.h"
#include "../external/openal-soft/include/AL/alext.h"

void NtshEngn::AudioModule::init() {
	// Open audio device
	m_device = alcOpenDevice(nullptr);
	if (!m_device) {
		NTSHENGN_MODULE_ERROR("Unable to open audio device.");
	}

	// Create context
	std::array<ALCint, 3> createContextAttribs = { ALC_HRTF_SOFT, ALC_FALSE, 0 };
	if (alcCall(alcCreateContext, m_context, m_device, m_device, createContextAttribs.data())) {
		if (!m_context) {
			NTSHENGN_MODULE_ERROR("Unable to create audio context.");
		}
	}

	// Make context current
	ALCboolean makeContextCurrent = ALC_FALSE;
	if (!alcCall(alcMakeContextCurrent, makeContextCurrent, m_device, m_context)) {
		if (makeContextCurrent != ALC_TRUE) {
			NTSHENGN_MODULE_ERROR("Unable to make audio context current.");
		}
	}
}

void NtshEngn::AudioModule::update(float dt) {
	NTSHENGN_UNUSED(dt);

	if (m_listenerEntity != NTSHENGN_ENTITY_UNKNOWN) {
		const SoundListener& listenerSoundListener = ecs->getComponent<SoundListener>(m_listenerEntity);
		const Transform& listenerTransform = ecs->getComponent<Transform>(m_listenerEntity);

		alListener3f(AL_POSITION, listenerTransform.position.x, listenerTransform.position.y, listenerTransform.position.z);

		const Math::vec3 baseSoundListenerDirection = Math::normalize(listenerSoundListener.forward);
		const float baseDirectionYaw = std::atan2(baseSoundListenerDirection.z, baseSoundListenerDirection.x);
		const float baseDirectionPitch = -std::asin(baseSoundListenerDirection.y);
		const Math::vec3 soundListenerDirection = Math::normalize(Math::vec3(
			std::cos(baseDirectionPitch + listenerTransform.rotation.x) * std::cos(baseDirectionYaw + listenerTransform.rotation.y),
			-std::sin(baseDirectionPitch + listenerTransform.rotation.x),
			std::cos(baseDirectionPitch + listenerTransform.rotation.x) * std::sin(baseDirectionYaw + listenerTransform.rotation.y)
		));
		std::array<float, 6> listenerOrientation = { soundListenerDirection.x, soundListenerDirection.y, soundListenerDirection.z, listenerSoundListener.up.x, listenerSoundListener.up.y, listenerSoundListener.up.z };
		alListenerfv(AL_ORIENTATION, listenerOrientation.data());
	}

	for (auto it = m_soundSourceIDToSoundSource.begin(); it != m_soundSourceIDToSoundSource.end(); ) {
		alCall(alGetSourcei, it->second.source, AL_SOURCE_STATE, &it->second.state);
		if (it->second.state == AL_STOPPED) {
			alCall(alDeleteSources, 1, &it->second.source);
			m_soundIDToSound[it->second.soundID].soundSourceIDs.erase(it->first);
			it = m_soundSourceIDToSoundSource.erase(it);
		}
		else {
			it++;
		}
	}
}

void NtshEngn::AudioModule::destroy() {
	for (auto& soundSource : m_soundSourceIDToSoundSource) {
		alCall(alSourceStop, soundSource.second.source);
		alCall(alDeleteSources, 1, &soundSource.second.source);
	}

	for (auto& sound : m_soundIDToSound) {
		alCall(alDeleteBuffers, 1, &sound.second.buffer);
	}

	alcMakeContextCurrent(m_context);
	alcDestroyContext(m_context);
	alcCloseDevice(m_device);
}

NtshEngn::SoundID NtshEngn::AudioModule::load(const Sound& sound) {
	OpenALSound newSound;
	
	// Generate buffer
	alCall(alGenBuffers, 1, &newSound.buffer);

	// Determine format
	ALenum format = 0;
	if (sound.channels == 1) {
		if (sound.bitsPerSample == 8) {
			format = AL_FORMAT_MONO8;
		}
		else if (sound.bitsPerSample == 16) {
			format = AL_FORMAT_MONO16;
		}
	}
	else if (sound.channels == 2) {
		if (sound.bitsPerSample == 8) {
			format = AL_FORMAT_STEREO8;
		}
		else if (sound.bitsPerSample == 16) {
			format = AL_FORMAT_STEREO16;
		}
	}

	if (format == 0) {
		NTSHENGN_MODULE_ERROR("Error finding the right format.");
	}

	alCall(alBufferData, newSound.buffer, format, sound.data.data(), static_cast<ALsizei>(sound.size), sound.sampleRate);

	m_soundIDToSound[m_soundID] = newSound;

	return m_soundID++;
}

NtshEngn::SoundSourceID NtshEngn::AudioModule::playSound(SoundID soundID, float gain, float pitch) {
	NTSHENGN_ASSERT(m_soundIDToSound.find(soundID) != m_soundIDToSound.end(), "SoundID " + std::to_string(soundID) + " does not exist.");

	OpenALSoundSource newSoundSource;
	alCall(alGenSources, 1, &newSoundSource.source);
	alCall(alSourcef, newSoundSource.source, AL_GAIN, gain);
	alCall(alSourcef, newSoundSource.source, AL_PITCH, pitch);
	alCall(alSourcei, newSoundSource.source, AL_SOURCE_RELATIVE, AL_TRUE);
	alCall(alSource3f, newSoundSource.source, AL_POSITION, 0.0f, 0.0f, 0.0f);
	alCall(alSource3f, newSoundSource.source, AL_VELOCITY, 0.0f, 0.0f, 0.0f);
	alCall(alSourcei, newSoundSource.source, AL_LOOPING, AL_FALSE);
	alCall(alSourcei, newSoundSource.source, AL_BUFFER, m_soundIDToSound[soundID].buffer);

	alCall(alSourcePlay, newSoundSource.source);

	newSoundSource.soundID = soundID;
	newSoundSource.state = AL_PLAYING;
	newSoundSource.gain = gain;
	newSoundSource.pitch = pitch;

	m_soundSourceIDToSoundSource[m_soundSourceID++] = newSoundSource;

	m_soundIDToSound[soundID].soundSourceIDs.insert(m_soundSourceID - 1);

	return m_soundSourceID - 1;
}

NtshEngn::SoundSourceID NtshEngn::AudioModule::playSoundAtPosition(SoundID soundID, const Math::vec3& position, float gain, float pitch) {
	NTSHENGN_ASSERT(m_soundIDToSound.find(soundID) != m_soundIDToSound.end(), "SoundID " + std::to_string(soundID) + " does not exist.");

	OpenALSoundSource newSoundSource;
	alCall(alGenSources, 1, &newSoundSource.source);
	alCall(alSourcef, newSoundSource.source, AL_GAIN, gain);
	alCall(alSourcef, newSoundSource.source, AL_PITCH, pitch);
	alCall(alSourcei, newSoundSource.source, AL_SOURCE_SPATIALIZE_SOFT, AL_TRUE);
	alCall(alSourcei, newSoundSource.source, AL_SOURCE_RELATIVE, AL_FALSE);
	alCall(alSource3f, newSoundSource.source, AL_POSITION, position.x, position.y, position.z);
	alCall(alSource3f, newSoundSource.source, AL_VELOCITY, 0.0f, 0.0f, 0.0f);
	alCall(alSourcei, newSoundSource.source, AL_LOOPING, AL_FALSE);
	alCall(alSourcei, newSoundSource.source, AL_BUFFER, m_soundIDToSound[soundID].buffer);

	alCall(alSourcePlay, newSoundSource.source);

	newSoundSource.soundID = soundID;
	newSoundSource.state = AL_PLAYING;
	newSoundSource.position = position;
	newSoundSource.gain = gain;
	newSoundSource.pitch = pitch;

	m_soundSourceIDToSoundSource[m_soundSourceID++] = newSoundSource;

	m_soundIDToSound[soundID].soundSourceIDs.insert(m_soundSourceID - 1);

	return m_soundSourceID - 1;
}

void NtshEngn::AudioModule::resumeSoundSource(SoundSourceID soundSourceID) {
	NTSHENGN_ASSERT(m_soundSourceIDToSoundSource.find(soundSourceID) != m_soundSourceIDToSoundSource.end(), "SoundSourceID " + std::to_string(soundSourceID) + " does not exist.");

	alCall(alSourcePlay, m_soundSourceIDToSoundSource[soundSourceID].source);
	m_soundSourceIDToSoundSource[soundSourceID].state = AL_PLAYING;
}

void NtshEngn::AudioModule::pauseSoundSource(SoundSourceID soundSourceID) {
	NTSHENGN_ASSERT(m_soundSourceIDToSoundSource.find(soundSourceID) != m_soundSourceIDToSoundSource.end(), "SoundSourceID " + std::to_string(soundSourceID) + " does not exist.");

	alCall(alSourcePause, m_soundSourceIDToSoundSource[soundSourceID].source);
	m_soundSourceIDToSoundSource[soundSourceID].state = AL_PAUSED;
}

void NtshEngn::AudioModule::stopSoundSource(SoundSourceID soundSourceID) {
	NTSHENGN_ASSERT(m_soundSourceIDToSoundSource.find(soundSourceID) != m_soundSourceIDToSoundSource.end(), "SoundSourceID " + std::to_string(soundSourceID) + " does not exist.");

	alCall(alSourceStop, m_soundSourceIDToSoundSource[soundSourceID].source);
	alCall(alDeleteSources, 1, &m_soundSourceIDToSoundSource[soundSourceID].source);
	m_soundIDToSound[m_soundSourceIDToSoundSource[soundSourceID].soundID].soundSourceIDs.erase(soundSourceID);
	m_soundSourceIDToSoundSource.erase(soundSourceID);
}

NtshEngn::SoundSourceState NtshEngn::AudioModule::getSoundSourceState(SoundSourceID soundSourceID) {
	if (m_soundSourceIDToSoundSource.find(soundSourceID) == m_soundSourceIDToSoundSource.end()) {
		return SoundSourceState::Stopped;
	}

	if (m_soundSourceIDToSoundSource[soundSourceID].state == AL_PLAYING) {
		return SoundSourceState::Playing;
	}
	else if (m_soundSourceIDToSoundSource[soundSourceID].state == AL_PAUSED) {
		return SoundSourceState::Paused;
	}
	else if (m_soundSourceIDToSoundSource[soundSourceID].state == AL_STOPPED) {
		return SoundSourceState::Stopped;
	}

	return SoundSourceState::Stopped;
}

bool NtshEngn::AudioModule::isSoundPlaying(SoundID soundID) {
	NTSHENGN_ASSERT(m_soundIDToSound.find(soundID) != m_soundIDToSound.end(), "SoundID " + std::to_string(soundID) + " does not exist.");

	for (auto& soundSourceID : m_soundIDToSound[soundID].soundSourceIDs) {
		if (m_soundSourceIDToSoundSource[soundSourceID].state == AL_PLAYING) {
			return true;
		}
	}

	return false;
}

void NtshEngn::AudioModule::setSoundSourcePosition(SoundSourceID soundSourceID, const Math::vec3& newPosition) {
	NTSHENGN_ASSERT(m_soundSourceIDToSoundSource.find(soundSourceID) != m_soundSourceIDToSoundSource.end(), "SoundSourceID " + std::to_string(soundSourceID) + " does not exist.");

	alCall(alSource3f, m_soundSourceIDToSoundSource[soundSourceID].source, AL_POSITION, newPosition.x, newPosition.y, newPosition.z);
	m_soundSourceIDToSoundSource[soundSourceID].position = newPosition;
}

NtshEngn::Math::vec3 NtshEngn::AudioModule::getSoundSourcePosition(SoundSourceID soundSourceID)  {
	NTSHENGN_ASSERT(m_soundSourceIDToSoundSource.find(soundSourceID) != m_soundSourceIDToSoundSource.end(), "SoundSourceID " + std::to_string(soundSourceID) + " does not exist.");

	return m_soundSourceIDToSoundSource[soundSourceID].position;
}

void NtshEngn::AudioModule::setSoundSourceGain(SoundSourceID soundSourceID, float newGain) {
	NTSHENGN_ASSERT(m_soundSourceIDToSoundSource.find(soundSourceID) != m_soundSourceIDToSoundSource.end(), "SoundSourceID " + std::to_string(soundSourceID) + " does not exist.");

	alCall(alSourcef, m_soundSourceIDToSoundSource[soundSourceID].source, AL_GAIN, newGain);
	m_soundSourceIDToSoundSource[soundSourceID].gain = newGain;
}

float NtshEngn::AudioModule::getSoundSourceGain(SoundSourceID soundSourceID) {
	NTSHENGN_ASSERT(m_soundSourceIDToSoundSource.find(soundSourceID) != m_soundSourceIDToSoundSource.end(), "SoundSourceID " + std::to_string(soundSourceID) + " does not exist.");

	return m_soundSourceIDToSoundSource[soundSourceID].gain;
}

void NtshEngn::AudioModule::setSoundSourcePitch(SoundSourceID soundSourceID, float newPitch) {
	NTSHENGN_ASSERT(m_soundSourceIDToSoundSource.find(soundSourceID) != m_soundSourceIDToSoundSource.end(), "SoundSourceID " + std::to_string(soundSourceID) + " does not exist.");

	alCall(alSourcef, m_soundSourceIDToSoundSource[soundSourceID].source, AL_PITCH, newPitch);
	m_soundSourceIDToSoundSource[soundSourceID].pitch = newPitch;
}

float NtshEngn::AudioModule::getSoundSourcePitch(SoundSourceID soundSourceID) {
	NTSHENGN_ASSERT(m_soundSourceIDToSoundSource.find(soundSourceID) != m_soundSourceIDToSoundSource.end(), "SoundSourceID " + std::to_string(soundSourceID) + " does not exist.");

	return m_soundSourceIDToSoundSource[soundSourceID].pitch;
}

const NtshEngn::ComponentMask NtshEngn::AudioModule::getComponentMask() const {
	ComponentMask componentMask;
	componentMask.set(ecs->getComponentID<SoundListener>());

	return componentMask;
}

void NtshEngn::AudioModule::onEntityComponentAdded(Entity entity, Component componentID) {
	if (componentID == ecs->getComponentID<SoundListener>()) {
		if (m_listenerEntity == NTSHENGN_ENTITY_UNKNOWN) {
			m_listenerEntity = entity;
		}
	}
}

void NtshEngn::AudioModule::onEntityComponentRemoved(Entity entity, Component componentID) {
	if (componentID == ecs->getComponentID<SoundListener>()) {
		if (m_listenerEntity == entity) {
			m_listenerEntity = NTSHENGN_ENTITY_UNKNOWN;
		}
	}
}

extern "C" NTSHENGN_MODULE_API NtshEngn::AudioModuleInterface* createModule() {
	return new NtshEngn::AudioModule;
}

extern "C" NTSHENGN_MODULE_API void destroyModule(NtshEngn::AudioModuleInterface* m) {
	delete m;
}