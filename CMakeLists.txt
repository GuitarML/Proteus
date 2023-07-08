cmake_minimum_required(VERSION 3.15)
project(Proteus VERSION 1.2.0)
include(CheckIPOSupported)

set(CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_OSX_DEPLOYMENT_TARGET "10.12" CACHE STRING "Minimum OS X deployment target")

option(BUILD_AU "" APPLE)
option(BUILD_AU3 "" APPLE)

option(BUILD_VST3 "" ON) # VST 2 requires a separate SDK so it's omitted

set(LINUX CMAKE_SYSTEM_NAME STREQUAL "Linux")
option(BUILD_LV2 "" LINUX)

option(BUILD_CLAP "" ON)
option(BUILD_AAX "" OFF)
option(BUILD_STANDALONE "" ON)

option(ENABLE_LTO "" ON)

check_ipo_supported(RESULT result OUTPUT output)
if(result AND ENABLE_LTO)
    set_property(GLOBAL PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
    message(STATUS "Enabled IPO")
else()
    message(WARNING "IPO is disabled or not supported. ${output}")
endif()

message(STATUS "Compiler:" ${CMAKE_CXX_COMPILER})
# On Linux, clang is also GNU in CMAKE_CXX_COMPILER_ID
# You need to pass compiler as CXX=/usr/bin/clang++ explicitly as on Linux
# the default compiler is /usr/bin/c++, and cmake can't generally follow symlinks
if (CMAKE_CXX_COMPILER MATCHES "clang")
    option(CLANG_NEW_PASS_MANAGER "Enable experimental pass manager on modern clang builds" ON)

    if (CLANG_NEW_PASS_MANAGER)
        message(STATUS "Using clang experimental pass manager")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexperimental-new-pass-manager")
    endif()
endif()

add_subdirectory(modules)
include_directories(modules)
add_subdirectory(modules/clap-juce-extensions)

if (UNIX)
    set(LINK_FLAGS "${LINK_FLAGS} -Wl --as-needed")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -Wpedantic")

    if (CMAKE_BUILD_TYPE STREQUAL "Release")
        set(LINK_FLAGS "${LINK_FLAGS} -s")
    endif()
endif()

set(JUCE_FORMATS "")

if (BUILD_AU)
    list(APPEND JUCE_FORMATS AU)
endif()

if (BUILD_AU3)
    list(APPEND JUCE_FORMATS AUv3)
endif()

if (BUILD_VST3)
    list(APPEND JUCE_FORMATS VST3)
endif()

if (BUILD_LV2)
    list(APPEND JUCE_FORMATS LV2)
endif()

if (BUILD_STANDALONE)
    list(APPEND JUCE_FORMATS Standalone)
endif()

if (BUILD_AAX)
    option(JUCE_AAX_SDK "Path to JUCE AAX SDK" "")
    juce_set_aax_sdk_path(JUCE_AAX_SDK)

    if (TARGET juce_aax_sdk)
        list(APPEND JUCE_FORMATS AAX)
    else()
        message(FATAL "JUCE AAX SDK missing")
    endif()
endif()

message(STATUS "Building ${JUCE_FORMATS}")

juce_add_plugin(Proteus
    COMPANY_NAME GuitarML
    PLUGIN_MANUFACTURER_CODE GtML
    PLUGIN_CODE Prt3
    FORMATS ${JUCE_FORMATS}
    ProductName "Proteus"
    LV2URI https://github.com/GuitarML/Proteus
    ICON_BIG resources/logo.png
    VST3_CATEGORIES Fx Distortion
    AU_MAIN_TYPE kAudioUnitType_Effect
    AAX_CATEGORY AAX_ePlugInCategory_Harmonic
    MICROPHONE_PERMISSION_ENABLED TRUE
)

if (BUILD_CLAP)
    clap_juce_extensions_plugin(TARGET Proteus
        CLAP_ID "com.guitarml.proteus"
        CLAP_FEATURES audio-effect filter)

    add_custom_target(BuildCLAP ALL DEPENDS Proteus_CLAP)
endif()

juce_generate_juce_header(Proteus)

# add sources
add_subdirectory(src)
include_directories(src)
add_subdirectory(resources)

target_compile_definitions(Proteus
    PUBLIC
    JUCE_DISPLAY_SPLASH_SCREEN=0
    JUCE_REPORT_APP_USAGE=0
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
    JUCE_VST3_CAN_REPLACE_VST2=0
    JUCE_MODAL_LOOPS_PERMITTED=1
    # We do not set e.g. JUCE_PLUGINHOST_LADSPA=BUILD_LV so as we could re-run cmake without
    # re-building all from scratch if we want to build LV2
    JUCE_USE_XINERAMA=0 # Use XRandr instead
)

target_link_libraries(Proteus PUBLIC juce::juce_recommended_lto_flags)
target_link_libraries(Proteus PUBLIC juce::juce_recommended_config_flags)
target_link_libraries(Proteus PUBLIC juce_plugin_modules)

message(STATUS "CXX flags: ${CMAKE_CXX_FLAGS}")
message(STATUS "Linker flags: ${LINK_FLAGS}")
