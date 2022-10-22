#include "ntsh_audio_module.h"
#include "../external/Module/ntsh_dynamic_library.h"
#include "../external/Common/ntsh_engine_defines.h"
#include "../external/Common/ntsh_engine_enums.h"

void NutshellAudioModule::init() {
	// Open audio device
	m_device = alcOpenDevice(nullptr);
	if (!m_device) {
		NTSH_MODULE_ERROR("Unable to open audio device.", NTSH_RESULT_MODULE_ERROR);
	}

	// Open context
	if (alcCall(alcCreateContext, m_context, m_device, m_device, nullptr)) {
		if (!m_context) {
			NTSH_MODULE_ERROR("Unable to create audio context.", NTSH_RESULT_MODULE_ERROR);
		}
	}

	// Make context current
	ALCboolean makeContextCurrent = ALC_FALSE;
	if (!alcCall(alcMakeContextCurrent, makeContextCurrent, m_device, m_context)) {
		if (makeContextCurrent != ALC_TRUE) {
			NTSH_MODULE_ERROR("Unable to make audio context current.", NTSH_RESULT_MODULE_ERROR);
		}
	}
}

void NutshellAudioModule::update(double dt) {
	NTSH_UNUSED(dt);
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

void NutshellAudioModule::destroy() {
	alcMakeContextCurrent(m_context);
	alcDestroyContext(m_context);
	alcCloseDevice(m_device);
}

NtshAudioId NutshellAudioModule::play(const NtshAudio& audio) {
	NTSH_UNUSED(audio);
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
	return 0;
}

void NutshellAudioModule::pause(NtshAudioId audioId) {
	NTSH_UNUSED(audioId);
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

void NutshellAudioModule::stop(NtshAudioId audioId) {
	NTSH_UNUSED(audioId);
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

bool NutshellAudioModule::isPlaying(NtshAudioId audioId) {
	NTSH_UNUSED(audioId);
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
	return false;
}

void NutshellAudioModule::setGain(NtshAudioId audioId, float newGain) {
	NTSH_UNUSED(audioId);
	NTSH_UNUSED(newGain);
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

float NutshellAudioModule::getGain(NtshAudioId audioId) {
	NTSH_UNUSED(audioId);
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
	return 0.0f;
}

void NutshellAudioModule::setPitch(NtshAudioId audioId, float newPitch) {
	NTSH_UNUSED(audioId);
	NTSH_UNUSED(newPitch);
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

float NutshellAudioModule::getPitch(NtshAudioId audioId) {
	NTSH_UNUSED(audioId);
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
	return 0.0f;
}

extern "C" NTSH_MODULE_API NutshellAudioModuleInterface* createModule() {
	return new NutshellAudioModule;
}

extern "C" NTSH_MODULE_API void destroyModule(NutshellAudioModuleInterface* m) {
	delete m;
}