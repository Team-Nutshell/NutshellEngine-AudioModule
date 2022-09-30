#include "ntsh_audio_module.h"
#include "../external/Module/ntsh_module_defines.h"
#include "../external/Module/ntsh_dynamic_library.h"
#include "../external/Common/ntsh_engine_enums.h"

void NutshellAudioModule::init() {
    NTSH_MODULE_ERROR("init() function not implemented.", NTSH_RESULT_MODULE_FUNCTION_NOT_IMPLEMENTED);
}

void NutshellAudioModule::update(double dt) {
    NTSH_UNUSED(dt);
    NTSH_MODULE_ERROR("update() function not implemented.", NTSH_RESULT_MODULE_FUNCTION_NOT_IMPLEMENTED);
}

void NutshellAudioModule::destroy() {
    NTSH_MODULE_ERROR("destroy() function not implemented.", NTSH_RESULT_MODULE_FUNCTION_NOT_IMPLEMENTED);
}

extern "C" NTSH_MODULE_API NutshellAudioModuleInterface * createModule() {
    return new NutshellAudioModule;
}

extern "C" NTSH_MODULE_API void destroyModule(NutshellAudioModuleInterface * m) {
    delete m;
}