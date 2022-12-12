#include "ntsh_audio_module.h"
#include "../external/Module/utils/ntsh_dynamic_library.h"
#include "../external/Common/utils/ntsh_engine_defines.h"
#include "../external/Common/utils/ntsh_engine_enums.h"

void NutshellAudioModule::init() {
	// Open audio device
	m_device = alcOpenDevice(nullptr);
	if (!m_device) {
		NTSH_MODULE_ERROR("Unable to open audio device.", NtshResult::ModuleError);
	}

	// Open context
	if (alcCall(alcCreateContext, m_context, m_device, m_device, nullptr)) {
		if (!m_context) {
			NTSH_MODULE_ERROR("Unable to create audio context.", NtshResult::ModuleError);
		}
	}

	// Make context current
	ALCboolean makeContextCurrent = ALC_FALSE;
	if (!alcCall(alcMakeContextCurrent, makeContextCurrent, m_device, m_context)) {
		if (makeContextCurrent != ALC_TRUE) {
			NTSH_MODULE_ERROR("Unable to make audio context current.", NtshResult::ModuleError);
		}
	}
}

void NutshellAudioModule::update(double dt) {
	NTSH_UNUSED(dt);

	for (NtshAudioId id = 0; id < m_id; id++) {
		if (isPlaying(id)) {
			alCall(alGetSourcei, m_idToSound[id].source, AL_SOURCE_STATE, &m_idToSound[id].state);
		}
	}
}

void NutshellAudioModule::destroy() {
	for (NtshAudioId id = 0; id < m_id; id++) {
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

NtshAudioId NutshellAudioModule::load(const NtshAudio audio) {
	OpenALSound newSound;
	
	// Generate buffer
	alCall(alGenBuffers, 1, &newSound.buffer);

	// Determine format
	ALenum format = 0;
	if (audio.channels == 1) {
		if (audio.bitsPerSample == 8) {
			format = AL_FORMAT_MONO8;
		}
		else if (audio.bitsPerSample == 16) {
			format = AL_FORMAT_MONO16;
		}
	}
	else if (audio.channels == 2) {
		if (audio.bitsPerSample == 8) {
			format = AL_FORMAT_STEREO8;
		}
		else if (audio.bitsPerSample == 16) {
			format = AL_FORMAT_STEREO16;
		}
	}

	if (format == 0) {
		NTSH_MODULE_ERROR("Error finding the right format.", NtshResult::ModuleError);
	}

	alCall(alBufferData, newSound.buffer, format, audio.data.data(), static_cast<ALsizei>(audio.size), audio.sampleRate);
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

void NutshellAudioModule::play(NtshAudioId audioId) {
	alCall(alSourcePlay, m_idToSound[audioId].source);
	m_idToSound[audioId].state = AL_PLAYING;
}

void NutshellAudioModule::pause(NtshAudioId audioId) {
	alCall(alSourcePause, m_idToSound[audioId].source);
	m_idToSound[audioId].state = AL_PAUSED;
}

void NutshellAudioModule::stop(NtshAudioId audioId) {
	alCall(alSourceStop, m_idToSound[audioId].source);
	m_idToSound[audioId].state = AL_STOPPED;
}

bool NutshellAudioModule::isPlaying(NtshAudioId audioId) {
	return m_idToSound[audioId].state == AL_PLAYING;
}

void NutshellAudioModule::setGain(NtshAudioId audioId, float newGain) {
	alCall(alSourcef, m_idToSound[audioId].source, AL_GAIN, newGain);
	m_idToSound[audioId].gain = newGain;
}

float NutshellAudioModule::getGain(NtshAudioId audioId) {
	return m_idToSound[audioId].gain;
}

void NutshellAudioModule::setPitch(NtshAudioId audioId, float newPitch) {
	alCall(alSourcef, m_idToSound[audioId].source, AL_PITCH, newPitch);
	m_idToSound[audioId].pitch = newPitch;
}

float NutshellAudioModule::getPitch(NtshAudioId audioId) {
	return m_idToSound[audioId].pitch;
}

extern "C" NTSH_MODULE_API NutshellAudioModuleInterface* createModule() {
	return new NutshellAudioModule;
}

extern "C" NTSH_MODULE_API void destroyModule(NutshellAudioModuleInterface* m) {
	delete m;
}