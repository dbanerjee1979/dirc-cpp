#ifndef CHARSET_FACTORY_H
#define CHARSET_FACTORY_H

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <boost/optional.hpp>
#include "charset.h"

namespace core {

class CharsetFactory {
public:
    CharsetFactory();
    const std::string &get_default_method();
    boost::optional<Charset &> find_charset(const std::string &name);
    std::vector<std::string> get_charsets();
private:
    std::vector<std::string> m_charset_names;
    std::unordered_map<std::string, std::unique_ptr<Charset>> m_charsets;
    static const std::string s_default_charset;
};

class DefaultCharset : public Charset {
public:
    DefaultCharset(const std::string &name);
    const std::string &description() const;
private:
    std::string m_description;
};

}

#endif // CHARSET_FACTORY_H
