#include "ntshengn_audio_module.h"
#include "../external/Module/utils/ntshengn_dynamic_library.h"
#include "../external/Common/utils/ntshengn_defines.h"
#include "../external/Common/utils/ntshengn_enums.h"

void NtshEngn::AudioModule::init() {
	// Open audio device
	m_device = alcOpenDevice(nullptr);
	if (!m_device) {
		NTSHENGN_MODULE_ERROR("Unable to open audio device.", NtshEngn::Result::ModuleError);
	}

	// Open context
	if (alcCall(alcCreateContext, m_context, m_device, m_device, nullptr)) {
		if (!m_context) {
			NTSHENGN_MODULE_ERROR("Unable to create audio context.", NtshEngn::Result::ModuleError);
		}
	}

	// Make context current
	ALCboolean makeContextCurrent = ALC_FALSE;
	if (!alcCall(alcMakeContextCurrent, makeContextCurrent, m_device, m_context)) {
		if (makeContextCurrent != ALC_TRUE) {
			NTSHENGN_MODULE_ERROR("Unable to make audio context current.", NtshEngn::Result::ModuleError);
		}
	}
}

void NtshEngn::AudioModule::update(double dt) {
	NTSHENGN_UNUSED(dt);

	for (NtshEngn::SoundId id = 0; id < m_id; id++) {
		if (isPlaying(id)) {
			alCall(alGetSourcei, m_idToSound[id].source, AL_SOURCE_STATE, &m_idToSound[id].state);
		}
	}
}

void NtshEngn::AudioModule::destroy() {
	for (NtshEngn::SoundId id = 0; id < m_id; id++) {
		if (isPlaying(id)) {
			stop(id);
		}
		alCall(alDeleteSources, 1, &m_idToSound[id].source);
		alCall(alDeleteBuffers, 1, &m_idToSound[id].buffer);
	}
	alcMakeContextCurrent(m_context);
	alcDestroyContext(m_context);
	alcCloseDevice(m_device);
}

NtshEngn::SoundId NtshEngn::AudioModule::load(const NtshEngn::Sound& sound) {
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
		NTSHENGN_MODULE_ERROR("Error finding the right format.", NtshEngn::Result::ModuleError);
	}

	alCall(alBufferData, newSound.buffer, format, sound.data.data(), static_cast<ALsizei>(sound.size), sound.sampleRate);
	alCall(alGenSources, 1, &newSound.source);
	alCall(alSourcef, newSound.source, AL_GAIN, 1.0f);
	alCall(alSourcef, newSound.source, AL_PITCH, 1.0f);
	alCall(alSource3f, newSound.source, AL_POSITION, 0.0f, 0.0f, 0.0f);
	alCall(alSource3f, newSound.source, AL_VELOCITY, 0.0f, 0.0f, 0.0f);
	alCall(alSourcei, newSound.source, AL_LOOPING, AL_FALSE);
	alCall(alSourcei, newSound.source, AL_BUFFER, newSound.buffer);

	m_idToSound[m_id] = newSound;

	return m_id++;
}

void NtshEngn::AudioModule::play(NtshEngn::SoundId audioId) {
	alCall(alSourcePlay, m_idToSound[audioId].source);
	m_idToSound[audioId].state = AL_PLAYING;
}

void NtshEngn::AudioModule::pause(NtshEngn::SoundId audioId) {
	alCall(alSourcePause, m_idToSound[audioId].source);
	m_idToSound[audioId].state = AL_PAUSED;
}

void NtshEngn::AudioModule::stop(NtshEngn::SoundId audioId) {
	alCall(alSourceStop, m_idToSound[audioId].source);
	m_idToSound[audioId].state = AL_STOPPED;
}

bool NtshEngn::AudioModule::isPlaying(NtshEngn::SoundId audioId) {
	return m_idToSound[audioId].state == AL_PLAYING;
}

void NtshEngn::AudioModule::setGain(NtshEngn::SoundId audioId, float newGain) {
	alCall(alSourcef, m_idToSound[audioId].source, AL_GAIN, newGain);
	m_idToSound[audioId].gain = newGain;
}

float NtshEngn::AudioModule::getGain(NtshEngn::SoundId audioId) {
	return m_idToSound[audioId].gain;
}

void NtshEngn::AudioModule::setPitch(NtshEngn::SoundId audioId, float newPitch) {
	alCall(alSourcef, m_idToSound[audioId].source, AL_PITCH, newPitch);
	m_idToSound[audioId].pitch = newPitch;
}

float NtshEngn::AudioModule::getPitch(NtshEngn::SoundId audioId) {
	return m_idToSound[audioId].pitch;
}

extern "C" NTSHENGN_MODULE_API NtshEngn::AudioModuleInterface* createModule() {
	return new NtshEngn::AudioModule;
}

extern "C" NTSHENGN_MODULE_API void destroyModule(NtshEngn::AudioModuleInterface* m) {
	delete m;
}