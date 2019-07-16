pkg_check_modules(GTKMM gtkmm-3.0)

include_directories(
    ${PROJECT_SOURCE_DIR}
    ${GTKMM_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIRS}
    )

add_library(gtk
    main.cpp
    network_list_dialog.cpp
    network_edit_dialog.cpp
    )

target_link_libraries(
    gtk
    core
    config
    ${GTKMM_LIBRARIES}
    ${Boost_LIBRARIES}
    )
