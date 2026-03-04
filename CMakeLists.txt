cmake_minimum_required(VERSION 3.15)

project(pils VERSION 1.0.0 LANGUAGES C CXX)

find_package(CURL REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(JUCE_USE_GTK ON)

add_subdirectory(external/JUCE)
add_subdirectory(src/pils-kernel)
add_subdirectory(src/pilsplug)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
pkg_check_modules(WEBKIT REQUIRED webkit2gtk-4.1)

set(JUCE_WEB_BROWSER 0)
juce_add_gui_app(pils_app PRODUCT_NAME "Pils")

set_target_properties(pils_app PROPERTIES
    OUTPUT_NAME "pils"
)

target_include_directories(pils_app PRIVATE
    ${GTK3_INCLUDE_DIRS}
    ${WEBKIT_INCLUDE_DIRS})
target_link_libraries(pils_app PRIVATE
    ${GTK3_LIBRARIES}
    ${WEBKIT_LIBRARIES})

file(GLOB JPILS_SOURCES
    src/jpils/jpils.cpp
    src/jpils/jpils-autodefine.cpp
    src/jpils/jpils-autoplumming.cpp
    src/jpils/jpils-binding-base.cpp
    src/jpils/jpils-commander.cpp
    src/jpils/jpils-file.cpp
    src/jpils/jpils-graph.cpp
    src/jpils/jpils-heap.cpp
    src/jpils/jpils-plumming.cpp
    src/jpils/jpils-standard-specials.cpp
    src/jpils/jpils-supplement.cpp
    src/jpils/jpils-thread.cpp
    src/jpils/pils_boot_expression.cpp
    src/jpils/pils_configuration_get_user_language.cpp
)

target_sources(pils_app PRIVATE
    #src/main.cpp
    ${JPILS_SOURCES}
)

target_compile_options(pils_app PRIVATE
    -Wall
    -Wextra
    -Wsuggest-override
    -Werror=suggest-override
)

target_link_libraries(pils_app PRIVATE
    juce::juce_core
    juce::juce_events
    juce::juce_data_structures
    juce::juce_graphics
    juce::juce_gui_basics
    juce::juce_gui_extra

    juce::juce_audio_basics
    juce::juce_audio_devices
    juce::juce_audio_formats
    juce::juce_audio_processors
    juce::juce_audio_utils

    juce::juce_cryptography
    juce::juce_opengl

    pils_kernel
    pilsplug
    CURL::libcurl
)
