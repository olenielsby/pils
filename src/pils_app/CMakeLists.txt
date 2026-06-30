add_executable(pils_app
    main.cpp
)

# Valgfrit: gør output-navn pænt
set_target_properties(pils_app PROPERTIES
    OUTPUT_NAME "pils"
)

target_link_libraries(pils_app PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::Network
    pils_kernel
    pils_qtbinding
)

target_compile_features(pils_app PRIVATE cxx_std_17)

enable_asan(pils_app)
