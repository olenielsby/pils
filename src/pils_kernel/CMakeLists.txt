file(GLOB KERNEL_SOURCES *.cpp)

add_library(pils_kernel STATIC ${KERNEL_SOURCES})

set_target_properties(pils_kernel PROPERTIES
    POSITION_INDEPENDENT_CODE ON
)

target_include_directories(pils_kernel PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(pils_kernel PUBLIC Qt6::Core)

enable_asan(pils_kernel)
