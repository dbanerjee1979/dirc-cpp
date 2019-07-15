#ifndef CHARSET_FACTORY_H
#define CHARSET_FACTORY_H

#include <string>
#include <unordered_map>
#include <memory>
#include <boost/optional.hpp>
#include "charset.h"

namespace core {

class CharsetFactory {
public:
    CharsetFactory();
    const std::string &get_default_method();
    boost::optional<Charset &> find_login_method(const std::string &name);

private:
    std::unordered_map<std::string, std::unique_ptr<Charset>> m_charsets;
    static const std::string s_default_charset;
};

class DefaultCharset : public Charset {
};

}

#endif // CHARSET_FACTORY_H
