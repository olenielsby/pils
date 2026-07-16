file(GLOB PILS_QT_SOURCES *.cpp)
file(GLOB PILS_QT_HEADERS *.h)

add_library(pils_qtbinding STATIC
    ${PILS_QT_SOURCES}
    ${PILS_QT_HEADERS}
)

#[[add_library(pils_qtbinding STATIC
    pils_boot_expression.cpp
    pils_configuration_get_user_language.cpp
    qpils_commander.cpp
    qpils_converter.cpp
    qpils_event.cpp
    qpils_file.cpp
    qpils_plumming.cpp
    qpils_qobject_wrapper.cpp
    qpils_registry.cpp
    qpils_signal.cpp
    qpils_specialized_node.cpp
    qpils_standard_specials.cpp
    qpils_supplement.cpp
    qpils_thread.cpp
    registry.h
)]]

target_include_directories(pils_qtbinding PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    /usr/lib/llvm-18/include
)

target_link_libraries(pils_qtbinding PUBLIC
    Qt6::Core
    Qt6::Widgets
    Qt6::Network
    pils_kernel
    /usr/lib/llvm-18/lib/libclang.so
)

target_compile_features(pils_qtbinding PUBLIC cxx_std_17)

enable_asan(pils_qtbinding)

