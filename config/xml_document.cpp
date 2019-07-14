#include <stdexcept>
#include <memory>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>
#include "xml_document.h"

namespace xml {

Document::Document(xercesc::DOMDocument *document,
                   xercesc::DOMImplementationLS *impl) :
        m_impl(impl),
        m_document(document) {
}

Document::~Document() {
    m_document->release();
}

void Document::save_file(const std::string &filename) {
    xercesc::DOMLSSerializer *serializer = m_impl->createLSSerializer();
    if (serializer->getDomConfig()->canSetParameter(xercesc::XMLUni::fgDOMWRTFormatPrettyPrint, true)) {
        serializer->getDomConfig()->setParameter(xercesc::XMLUni::fgDOMWRTFormatPrettyPrint, true);
    }
    auto output = m_impl->createLSOutput();
    try {
        auto x_filename = std::unique_ptr<XMLCh>(new XMLCh[filename.size() + 1]);
        xercesc::XMLString::transcode(filename.c_str(), x_filename.get(), filename.size());
        auto format = std::unique_ptr<xercesc::LocalFileFormatTarget>(new xercesc::LocalFileFormatTarget(x_filename.get()));
        output->setByteStream(format.get());
        serializer->write(m_document, output);
    }
    catch (xercesc::XMLException &ex) {
        const XMLCh *x_msg = ex.getMessage();
        char *c_msg = xercesc::XMLString::transcode(x_msg);
        std::string msg(c_msg);
        xercesc::XMLString::release(&c_msg);
        throw std::runtime_error(msg);
    }
    catch (xercesc::DOMException &ex) {
        const XMLCh *x_msg = ex.getMessage();
        char *c_msg = xercesc::XMLString::transcode(x_msg);
        std::string msg(c_msg);
        xercesc::XMLString::release(&c_msg);
        throw std::runtime_error(msg);
    }
    output->release();
    serializer->release();
}

Element Document::get_root() {
    return Element(m_document->getDocumentElement(), m_document);
}

}
