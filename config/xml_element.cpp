#include <boost/algorithm/string.hpp>
#include "xml_element.h"

namespace xml {

Element::Element(xercesc::DOMElement *element, xercesc::DOMDocument *document) :
        m_element(element), m_document(document) {
}

std::string Element::get_name() const {
    const XMLCh *x_name = m_element->getTagName();
    char *c_name = xercesc::XMLString::transcode(x_name);
    std::string name(c_name);
    xercesc::XMLString::release(&c_name);
    return name;
}

std::string Element::get_text() const {
    const XMLCh *x_text = m_element->getTextContent();
    char *c_text = xercesc::XMLString::transcode(x_text);
    std::string text(c_text);
    xercesc::XMLString::release(&c_text);
    return text;
}

void Element::set_text(const std::string &text) {
    size_t n = text.size();
    auto x_text = std::unique_ptr<XMLCh>(new XMLCh[n + 1]);
    xercesc::XMLString::transcode(text.c_str(), x_text.get(), n);
    m_element->setTextContent(x_text.get());
}

bool Element::get_bool() const {
    return boost::iequals(boost::trim_copy(get_text()), "true");
}

void Element::set_bool(bool val) {
    set_text(val ? "true" : "false");
}

void Element::for_each(std::function<void(const xml::Element &)> h) const {
    xercesc::DOMNodeList *x_children = m_element->getChildNodes();
    for (unsigned i = 0; i < x_children->getLength(); i++) {
        xercesc::DOMNode *node = x_children->item(i);
        if (node->getNodeType() == xercesc::DOMElement::ELEMENT_NODE) {
            Element el = Element(dynamic_cast<xercesc::DOMElement *>(node), m_document);
            h(el);
        }
    }
}

Element Element::append_child(const std::string &name) {
    auto x_name = std::unique_ptr<XMLCh>(new XMLCh[name.size() + 1]);
    xercesc::XMLString::transcode(name.c_str(), x_name.get(), name.size());
    xercesc::DOMElement *child = m_document->createElement(x_name.get());
    m_element->appendChild(child);
    return Element(child, m_document);
}

}
