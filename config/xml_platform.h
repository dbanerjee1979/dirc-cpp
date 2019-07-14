#ifndef XML_PLATFORM_H
#define XML_PLATFORM_H

#include <xercesc/dom/DOM.hpp>
#include "xml_document.h"

namespace xml {

class Platform {
public:
    Platform();
    ~Platform();
    Document parse_file(const std::string &filename);
    Document create_document(const std::string &root_element);
private:
    xercesc::DOMImplementation *m_impl;
};

}

#endif // XML_PLATFORM_H
