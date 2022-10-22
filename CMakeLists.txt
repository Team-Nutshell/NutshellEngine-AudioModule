cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
set(NAME NutshellAudioModule)
project(${NAME} VERSION 0.0.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(NTSH_DEFINES "")

add_subdirectory(external/Module)
add_subdirectory(external/Common)

list(APPEND NTSH_DEFINES NTSH_CURRENT_MODULE_AUDIO)

add_subdirectory(external/openal-soft)

set(MODULE_SOURCES
	src/ntsh_audio_module.cpp)	
set(MODULE_HEADERS
	src/ntsh_audio_module.h)

set(SOURCES ${MODULE_SOURCES})
set(HEADERS ${MODULE_HEADERS})

add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} PRIVATE NutshellEngine::Module NutshellEngine::Common OpenAL)

target_compile_options(${PROJECT_NAME} PRIVATE
	$<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
	$<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Werror>)

target_compile_definitions(${PROJECT_NAME} PRIVATE
	${NTSH_DEFINES}
	PUBLIC
	$<$<CONFIG:Debug>:NTSH_DEBUG>
	$<$<CONFIG:MinSizeRel>:NTSH_RELEASE>
	$<$<CONFIG:Release>:NTSH_RELEASE>
	$<$<CONFIG:RelWithDebInfo>:NTSH_DEBUG>)

set_target_properties(${PROJECT_NAME}
	PROPERTIES
	DEFINE_SYMBOL "NutshellModule_EXPORTS")

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:OpenAL> ${PROJECT_BINARY_DIR}
	COMMENT "Copy OpenAL32 to project build folder.")