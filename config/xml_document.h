#ifndef XML_DOCUMENT_H
#define XML_DOCUMENT_H

#include <xercesc/dom/DOM.hpp>
#include "xml_element.h"

namespace xml {

class Document {
public:
    Document(xercesc::DOMDocument *document, xercesc::DOMImplementationLS *impl);
    ~Document();
    void save_file(const std::string &filename);
    Element get_root();
private:
    xercesc::DOMImplementationLS *m_impl;
    xercesc::DOMDocument *m_document;
};

}

#endif // XML_DOCUMENT_H
