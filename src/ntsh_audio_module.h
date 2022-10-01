#pragma once
#include "../external/Common/module_interfaces/ntsh_audio_module_interface.h"

class NutshellAudioModule : public NutshellAudioModuleInterface {
public:
	NutshellAudioModule() : NutshellAudioModuleInterface("Nutshell Audio Test Module") {}

	void init();
	void update(double dt);
	void destroy();
};