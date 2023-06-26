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

NtshEngn::SoundId NtshEngn::AudioModule::load(const Sound& sound) {
	NTSHENGN_UNUSED(sound);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();

	return std::numeric_limits<SoundId>::max();
}

void NtshEngn::AudioModule::play(SoundId audioId) {
	NTSHENGN_UNUSED(audioId);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

void NtshEngn::AudioModule::pause(SoundId audioId) {
	NTSHENGN_UNUSED(audioId);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

void NtshEngn::AudioModule::stop(SoundId audioId) {
	NTSHENGN_UNUSED(audioId);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

bool NtshEngn::AudioModule::isPlaying(SoundId audioId) {
	NTSHENGN_UNUSED(audioId);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();

	return false;
}

void NtshEngn::AudioModule::setGain(SoundId audioId, float newGain) {
	NTSHENGN_UNUSED(audioId);
	NTSHENGN_UNUSED(newGain);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

float NtshEngn::AudioModule::getGain(SoundId audioId) {
	NTSHENGN_UNUSED(audioId);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();

	return 0.0f;
}

void NtshEngn::AudioModule::setPitch(SoundId audioId, float newPitch) {
	NTSHENGN_UNUSED(audioId);
	NTSHENGN_UNUSED(newPitch);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

float NtshEngn::AudioModule::getPitch(SoundId audioId) {
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