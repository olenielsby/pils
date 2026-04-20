cmake_minimum_required(VERSION 3.21)

project(pils VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Qt automoc
set(CMAKE_AUTOMOC OFF)
set(CMAKE_AUTOUIC OFF)
set(CMAKE_AUTORCC OFF)

# Dependencies
find_package(Qt6 REQUIRED COMPONENTS Core Widgets Network)
find_package(CURL REQUIRED)

# Submodules
add_subdirectory(src/pils_kernel)
add_subdirectory(src/pils_qtbinding)
add_subdirectory(src/pils_app)

