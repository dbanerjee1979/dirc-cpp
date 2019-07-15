include_directories(
    ${PROJECT_SOURCE_DIR}
    )

add_library(gtk
    main.cpp
    )

target_link_libraries(
    gtk
    core
    config)
