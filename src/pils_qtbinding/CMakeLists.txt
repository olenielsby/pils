add_library(pils_qtbinding STATIC
    pils_boot_expression.cpp
    pils_configuration_get_user_language.cpp
    qpils_commander.cpp
    qpils_file.cpp
    qpils_plumming.cpp
    qpils_qobject_wrapper.cpp
    qpils_registry.cpp
    qpils_signal.cpp
    qpils_standard_specials.cpp
    qpils_thread.cpp
    qpils_converter.h qpils_converter.cpp
    qpils_specialized_node.h qpils_specialized_node.cpp
    registry.h
)

target_include_directories(pils_qtbinding PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(pils_qtbinding PUBLIC
    Qt6::Core
    Qt6::Widgets
    Qt6::Network
    pils_kernel
)

target_compile_features(pils_qtbinding PUBLIC cxx_std_17)
