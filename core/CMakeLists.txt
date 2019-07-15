include_directories(
    ${PROJECT_SOURCE_DIR}
    )

add_library(
    core
    login_method_factory.cpp
    charset_factory.cpp
    )
