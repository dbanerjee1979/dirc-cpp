#include <stdexcept>
#include <memory>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/XMLString.hpp>
#include "xml_platform.h"

namespace xml {

Platform::Platform() {
    try {
        xercesc::XMLPlatformUtils::Initialize();
        XMLCh type[10];
        xercesc::XMLString::transcode("LS", type, 9);
        m_impl = xercesc::DOMImplementationRegistry::getDOMImplementation(type);
    }
    catch (xercesc::XMLException &ex) {
        char *c_msg = xercesc::XMLString::transcode(ex.getMessage());
        std::string msg(c_msg);
        xercesc::XMLString::release(&c_msg);
        throw std::runtime_error(msg);
    }
}

Platform::~Platform() {
    xercesc::XMLPlatformUtils::Terminate();
}

Document Platform::parse_file(const std::string &filename) {
    try {
        auto parser = std::unique_ptr<xercesc::XercesDOMParser>(new xercesc::XercesDOMParser());
        parser->setValidationScheme(xercesc::XercesDOMParser::Val_Always);
        parser->setDoNamespaces(false);
        parser->parse(filename.c_str());
        parser->adoptDocument();
        return Document(parser->getDocument(), dynamic_cast<xercesc::DOMImplementationLS *>(m_impl));
    }
    catch (xercesc::DOMException &ex) {
        char *c_msg = xercesc::XMLString::transcode(ex.getMessage());
        std::string msg(c_msg);
        xercesc::XMLString::release(&c_msg);
        throw std::runtime_error(msg);
    }
    catch (xercesc::XMLException &ex) {
        char *c_msg = xercesc::XMLString::transcode(ex.getMessage());
        std::string msg(c_msg);
        xercesc::XMLString::release(&c_msg);
        throw std::runtime_error(msg);
    }
}

Document Platform::create_document(const std::string &root_element) {
    size_t n = root_element.size();
    auto x_name = std::unique_ptr<XMLCh>(new XMLCh[n + 1]);
    xercesc::XMLString::transcode(root_element.c_str(), x_name.get(), n);
    return Document(m_impl->createDocument(nullptr, x_name.get(), nullptr),
                    dynamic_cast<xercesc::DOMImplementationLS *>(m_impl));
}

}
