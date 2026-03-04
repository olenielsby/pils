file(GLOB PLUG_SOURCES *.cpp)

add_library(pilsplug STATIC ${PLUG_SOURCES})

target_include_directories(pilsplug
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(pilsplug
    PUBLIC
        pils_kernel
)
