#ifndef XML_ELEMENT_H
#define XML_ELEMENT_H

#include <functional>
#include <vector>
#include <string>
#include <xercesc/dom/DOM.hpp>

namespace xml {

class Element {
public:
    Element(xercesc::DOMElement *element, xercesc::DOMDocument *document);
    std::string get_name() const;
    std::string get_text() const;
    void set_text(const std::string &text);
    bool get_bool() const;
    void set_bool(bool val);
    void for_each(std::function<void(const xml::Element &)> h) const;
    void append_child(const std::string &name, std::function<void(xml::Element &)> h);
private:
    xercesc::DOMElement *m_element;
    xercesc::DOMDocument *m_document;
};

}

#endif // XML_ELEMENT_H
