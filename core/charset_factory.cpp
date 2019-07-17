#include <boost/algorithm/string.hpp>
#include "charset_factory.h"

namespace core {

const std::string CharsetFactory::s_default_charset = "UTF-8";

DefaultCharset::DefaultCharset(const std::string &description) :
        m_description(description) {
}

const std::string &DefaultCharset::description() const {
    return m_description;
}

CharsetFactory::CharsetFactory() :
        m_charset_names({
            "UTF-8", "CP1252", "ISO-8859-15", "ISO-8859-2", "ISO-8859-7", "ISO-8859-8",
            "ISO-8859-9", "ISO-2022-JP", "SJIS", "CP949", "KOI8-R", "CP1251", "CP1256",
            "CP1257", "GB18030", "TIS-620"
        }) {
    auto it = m_charset_names.begin();
    m_charsets[*(it++)] = std::unique_ptr<Charset>(new DefaultCharset("UTF-8 (Unicode)"));
    m_charsets[*(it++)] = std::unique_ptr<Charset>(new DefaultCharset("Windows-1252"));
    m_charsets[*(it++)] = std::unique_ptr<Charset>(new DefaultCharset("ISO-8859-15 (Western Europe)"));
    m_charsets[*(it++)] = std::unique_ptr<Charset>(new DefaultCharset("ISO-8859-2 (Central Europe)"));
    m_charsets[*(it++)] = std::unique_ptr<Charset>(new DefaultCharset("ISO-8859-7 (Greek)"));
    m_charsets[*(it++)] = std::unique_ptr<Charset>(new DefaultCharset("ISO-8859-8 (Hebrew)"));
    m_charsets[*(it++)] = std::unique_ptr<Charset>(new DefaultCharset("ISO-8859-9 (Turkish)"));
    m_charsets[*(it++)] = std::unique_ptr<Charset>(new DefaultCharset("ISO-2022-JP (Japanese)"));
    m_charsets[*(it++)] = std::unique_ptr<Charset>(new DefaultCharset("SJIS (Japanese)"));
    m_charsets[*(it++)] = std::unique_ptr<Charset>(new DefaultCharset("CP949 (Korean)"));
    m_charsets[*(it++)] = std::unique_ptr<Charset>(new DefaultCharset("KOI8-R (Cyrillic)"));
    m_charsets[*(it++)] = std::unique_ptr<Charset>(new DefaultCharset("CP1251 (Cyrillic)"));
    m_charsets[*(it++)] = std::unique_ptr<Charset>(new DefaultCharset("CP1256 (Arabic)"));
    m_charsets[*(it++)] = std::unique_ptr<Charset>(new DefaultCharset("CP1257 (Baltic)"));
    m_charsets[*(it++)] = std::unique_ptr<Charset>(new DefaultCharset("GB18030 (Chinese)"));
    m_charsets[*(it++)] = std::unique_ptr<Charset>(new DefaultCharset("TIS-620 (Thai)"));
}

const std::string &CharsetFactory::get_default_method() {
    return s_default_charset;
}

boost::optional<Charset &> CharsetFactory::find_charset(const std::string &name) {
    auto it = m_charsets.find(boost::to_upper_copy(name));
    if (it != m_charsets.end()) {
        return boost::optional<Charset &>(*(it->second));
    }
    else {
        return boost::none;
    }
}

std::vector<std::string> CharsetFactory::get_charsets() {
    return std::vector<std::string>(m_charset_names);
}

}
