file(GLOB KERNEL_SOURCES *.cpp)

add_library(pils_kernel STATIC ${KERNEL_SOURCES})

target_include_directories(pils_kernel PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

