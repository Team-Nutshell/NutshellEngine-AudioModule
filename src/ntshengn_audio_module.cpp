#include "ntshengn_audio_module.h"
#include "../Module/utils/ntshengn_module_defines.h"
#include "../Module/utils/ntshengn_dynamic_library.h"
#include "../Common/utils/ntshengn_defines.h"
#include "../Common/utils/ntshengn_enums.h"
#include <limits>

void NtshEngn::AudioModule::init() {
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

void NtshEngn::AudioModule::update(float dt) {
	NTSHENGN_UNUSED(dt);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

void NtshEngn::AudioModule::destroy() {
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

NtshEngn::SoundID NtshEngn::AudioModule::load(const Sound& sound) {
	NTSHENGN_UNUSED(sound);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();

	return NTSHENGN_SOUND_UNKNOWN;
}

NtshEngn::SoundSourceID NtshEngn::AudioModule::playSound(SoundID soundID, float gain, float pitch) {
	NTSHENGN_UNUSED(soundID);
	NTSHENGN_UNUSED(gain);
	NTSHENGN_UNUSED(pitch);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();

	return NTSHENGN_SOUND_SOURCE_UNKNOWN;
}

NtshEngn::SoundSourceID NtshEngn::AudioModule::playSoundAtPosition(SoundID soundID, const Math::vec3& position, float gain, float pitch) {
	NTSHENGN_UNUSED(soundID);
	NTSHENGN_UNUSED(position);
	NTSHENGN_UNUSED(gain);
	NTSHENGN_UNUSED(pitch);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();

	return NTSHENGN_SOUND_SOURCE_UNKNOWN;
}

void NtshEngn::AudioModule::resumeSoundSource(SoundSourceID soundSourceID) {
	NTSHENGN_UNUSED(soundSourceID);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

void NtshEngn::AudioModule::pauseSoundSource(SoundSourceID soundSourceID) {
	NTSHENGN_UNUSED(soundSourceID);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

void NtshEngn::AudioModule::stopSoundSource(SoundSourceID soundSourceID) {
	NTSHENGN_UNUSED(soundSourceID);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

NtshEngn::SoundSourceState NtshEngn::AudioModule::getSoundSourceState(SoundSourceID soundSourceID) {
	NTSHENGN_UNUSED(soundSourceID);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();

	return SoundSourceState::Stopped;
}

bool NtshEngn::AudioModule::isSoundPlaying(SoundID soundID) {
	NTSHENGN_UNUSED(soundID);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();

	return false;
}

void NtshEngn::AudioModule::setSoundSourcePosition(SoundSourceID soundSourceID, const Math::vec3& newPosition) {
	NTSHENGN_UNUSED(soundSourceID);
	NTSHENGN_UNUSED(newPosition);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

NtshEngn::Math::vec3 NtshEngn::AudioModule::getSoundSourcePosition(SoundSourceID soundSourceID) {
	NTSHENGN_UNUSED(soundSourceID);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();

	return Math::vec3(0.0f, 0.0f, 0.0f);
}

void NtshEngn::AudioModule::setSoundSourceGain(SoundSourceID soundSourceID, float newGain) {
	NTSHENGN_UNUSED(soundSourceID);
	NTSHENGN_UNUSED(newGain);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

float NtshEngn::AudioModule::getSoundSourceGain(SoundSourceID soundSourceID) {
	NTSHENGN_UNUSED(soundSourceID);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();

	return 0.0f;
}

void NtshEngn::AudioModule::setSoundSourcePitch(SoundSourceID soundSourceID, float newPitch) {
	NTSHENGN_UNUSED(soundSourceID);
	NTSHENGN_UNUSED(newPitch);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

float NtshEngn::AudioModule::getSoundSourcePitch(SoundSourceID soundSourceID) {
	NTSHENGN_UNUSED(soundSourceID);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();

	return 0.0f;
}

extern "C" NTSHENGN_MODULE_API NtshEngn::AudioModuleInterface* createModule() {
	return new NtshEngn::AudioModule;
}

extern "C" NTSHENGN_MODULE_API void destroyModule(NtshEngn::AudioModuleInterface* m) {
	delete m;
}