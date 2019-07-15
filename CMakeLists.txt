cmake_minimum_required(VERSION 2.8)

project(dirc-cpp)

set(CMAKE_BUILD_TYPE Debug)

find_package(XercesC)
find_package(PkgConfig)
find_package(Boost COMPONENTS regex)

add_subdirectory(core)
add_subdirectory(config)
add_subdirectory(gtk)

include_directories(
    .
    )

add_executable(
    dirc-gtk
    gtk)

target_link_libraries(
    dirc-gtk
    ${XercesC_LIBRARIES}
    core
    config
    gtk
    )
