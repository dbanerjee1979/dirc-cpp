#include <boost/algorithm/string.hpp>
#include "login_method_factory.h"

namespace core {

const std::string LoginMethodFactory::s_default_method = "DEFAULT";

LoginMethodFactory::LoginMethodFactory() {
    m_login_methods["DEFAULT"] = std::unique_ptr<LoginMethod>(new DefaultLoginMethod());
    m_login_methods["SASL"] = std::unique_ptr<LoginMethod>(new DefaultLoginMethod());
    m_login_methods["SASL_EXTERNAL"] = std::unique_ptr<LoginMethod>(new DefaultLoginMethod());
    m_login_methods["PASSWORD"] = std::unique_ptr<LoginMethod>(new DefaultLoginMethod());
    m_login_methods["NICKSERV_MSG"] = std::unique_ptr<LoginMethod>(new DefaultLoginMethod());
    m_login_methods["NICKSERV_CMD"] = std::unique_ptr<LoginMethod>(new DefaultLoginMethod());
    m_login_methods["CHALLENGE"] = std::unique_ptr<LoginMethod>(new DefaultLoginMethod());
    m_login_methods["CUSTOM"] = std::unique_ptr<LoginMethod>(new DefaultLoginMethod());
}

const std::string &LoginMethodFactory::get_default_method() {
    return s_default_method;
}

boost::optional<LoginMethod &> LoginMethodFactory::find_login_method(const std::string &name) {
    auto it = m_login_methods.find(boost::to_upper_copy(name));
    if (it != m_login_methods.end()) {
        return boost::optional<LoginMethod &>(*(it->second));
    }
    else {
        return boost::none;
    }
}

}
