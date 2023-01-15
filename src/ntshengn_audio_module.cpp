#include "ntshengn_audio_module.h"
#include "../external/Module/utils/ntshengn_module_defines.h"
#include "../external/Module/utils/ntshengn_dynamic_library.h"
#include "../external/Common/utils/ntshengn_defines.h"
#include "../external/Common/utils/ntshengn_enums.h"

void NtshEngn::AudioModule::init() {
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

void NtshEngn::AudioModule::update(double dt) {
	NTSHENGN_UNUSED(dt);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

void NtshEngn::AudioModule::destroy() {
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

NtshEngn::SoundId NtshEngn::AudioModule::load(const NtshEngn::Sound audio) {
	NTSHENGN_UNUSED(audio);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();
	return 0;
}

void NtshEngn::AudioModule::play(NtshEngn::SoundId audioId) {
	NTSHENGN_UNUSED(audioId);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

void NtshEngn::AudioModule::pause(NtshEngn::SoundId audioId) {
	NTSHENGN_UNUSED(audioId);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

void NtshEngn::AudioModule::stop(NtshEngn::SoundId audioId) {
	NTSHENGN_UNUSED(audioId);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

bool NtshEngn::AudioModule::isPlaying(NtshEngn::SoundId audioId) {
	NTSHENGN_UNUSED(audioId);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();
	return false;
}

void NtshEngn::AudioModule::setGain(NtshEngn::SoundId audioId, float newGain) {
	NTSHENGN_UNUSED(audioId);
	NTSHENGN_UNUSED(newGain);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

float NtshEngn::AudioModule::getGain(NtshEngn::SoundId audioId) {
	NTSHENGN_UNUSED(audioId);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();
	return 0.0f;
}

void NtshEngn::AudioModule::setPitch(NtshEngn::SoundId audioId, float newPitch) {
	NTSHENGN_UNUSED(audioId);
	NTSHENGN_UNUSED(newPitch);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

float NtshEngn::AudioModule::getPitch(NtshEngn::SoundId audioId) {
	NTSHENGN_UNUSED(audioId);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();
	return 0.0f;
}

extern "C" NTSHENGN_MODULE_API NtshEngn::AudioModuleInterface* createModule() {
	return new NtshEngn::AudioModule;
}

extern "C" NTSHENGN_MODULE_API void destroyModule(NtshEngn::AudioModuleInterface* m) {
	delete m;
}