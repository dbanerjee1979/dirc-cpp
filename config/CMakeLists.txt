include_directories(
    ${PROJECT_SOURCE_DIR}
    )

add_library(
    config
    dirc_config_elements.cpp
    xml_platform.cpp
    xml_element.cpp
    xml_document.cpp
    dirc_config_builder.cpp
    dirc_config_doc_builder.cpp
    )
