#include "ntsh_audio_module.h"
#include "../external/Module/utils/ntsh_module_defines.h"
#include "../external/Module/utils/ntsh_dynamic_library.h"
#include "../external/Common/utils/ntsh_engine_defines.h"
#include "../external/Common/utils/ntsh_engine_enums.h"

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

Ntsh::SoundId NutshellAudioModule::load(const Ntsh::Sound audio) {
	NTSH_UNUSED(audio);
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
	return 0;
}

void NutshellAudioModule::play(Ntsh::SoundId audioId) {
	NTSH_UNUSED(audioId);
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

void NutshellAudioModule::pause(Ntsh::SoundId audioId) {
	NTSH_UNUSED(audioId);
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

void NutshellAudioModule::stop(Ntsh::SoundId audioId) {
	NTSH_UNUSED(audioId);
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

bool NutshellAudioModule::isPlaying(Ntsh::SoundId audioId) {
	NTSH_UNUSED(audioId);
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
	return false;
}

void NutshellAudioModule::setGain(Ntsh::SoundId audioId, float newGain) {
	NTSH_UNUSED(audioId);
	NTSH_UNUSED(newGain);
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

float NutshellAudioModule::getGain(Ntsh::SoundId audioId) {
	NTSH_UNUSED(audioId);
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
	return 0.0f;
}

void NutshellAudioModule::setPitch(Ntsh::SoundId audioId, float newPitch) {
	NTSH_UNUSED(audioId);
	NTSH_UNUSED(newPitch);
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

float NutshellAudioModule::getPitch(Ntsh::SoundId audioId) {
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