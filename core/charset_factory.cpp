#include <boost/algorithm/string.hpp>
#include "charset_factory.h"

namespace core {

const std::string CharsetFactory::s_default_charset = "UTF-8";

CharsetFactory::CharsetFactory() {
    m_charsets["UTF-8"] = std::unique_ptr<Charset>(new DefaultCharset());
}

const std::string &CharsetFactory::get_default_method() {
    return s_default_charset;
}

boost::optional<Charset &> CharsetFactory::find_login_method(const std::string &name) {
    auto it = m_charsets.find(boost::to_upper_copy(name));
    if (it != m_charsets.end()) {
        return boost::optional<Charset &>(*(it->second));
    }
    else {
        return boost::none;
    }
}

}
