#include "ntshengn_audio_module.h"
#include "../external/Module/utils/ntshengn_module_defines.h"
#include "../external/Module/utils/ntshengn_dynamic_library.h"
#include "../external/Common/utils/ntshengn_defines.h"
#include "../external/Common/utils/ntshengn_enums.h"
#include <limits>

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

NtshEngn::SoundID NtshEngn::AudioModule::load(const Sound& sound) {
	NTSHENGN_UNUSED(sound);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();

	return std::numeric_limits<SoundID>::max();
}

void NtshEngn::AudioModule::play(SoundID soundID) {
	NTSHENGN_UNUSED(soundID);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

void NtshEngn::AudioModule::pause(SoundID soundID) {
	NTSHENGN_UNUSED(soundID);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

void NtshEngn::AudioModule::stop(SoundID soundID) {
	NTSHENGN_UNUSED(soundID);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

bool NtshEngn::AudioModule::isPlaying(SoundID soundID) {
	NTSHENGN_UNUSED(soundID);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();

	return false;
}

void NtshEngn::AudioModule::setGain(SoundID soundID, float newGain) {
	NTSHENGN_UNUSED(soundID);
	NTSHENGN_UNUSED(newGain);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

float NtshEngn::AudioModule::getGain(SoundID soundID) {
	NTSHENGN_UNUSED(soundID);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();

	return 0.0f;
}

void NtshEngn::AudioModule::setPitch(SoundID soundID, float newPitch) {
	NTSHENGN_UNUSED(soundID);
	NTSHENGN_UNUSED(newPitch);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

float NtshEngn::AudioModule::getPitch(SoundID soundID) {
	NTSHENGN_UNUSED(soundID);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();

	return 0.0f;
}

extern "C" NTSHENGN_MODULE_API NtshEngn::AudioModuleInterface* createModule() {
	return new NtshEngn::AudioModule;
}

extern "C" NTSHENGN_MODULE_API void destroyModule(NtshEngn::AudioModuleInterface* m) {
	delete m;
}