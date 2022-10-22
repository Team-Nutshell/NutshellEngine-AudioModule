#include "ntsh_audio_module.h"
#include "../external/Module/ntsh_module_defines.h"
#include "../external/Module/ntsh_dynamic_library.h"
#include "../external/Common/ntsh_engine_defines.h"
#include "../external/Common/ntsh_engine_enums.h"

void NutshellAudioModule::init() {
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

void NutshellAudioModule::update(double dt) {
	NTSH_UNUSED(dt);
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

void NutshellAudioModule::destroy() {
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
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