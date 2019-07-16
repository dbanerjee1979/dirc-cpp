#include <boost/algorithm/string.hpp>
#include "login_method_factory.h"

namespace core {

const std::string LoginMethodFactory::s_default_method = "DEFAULT";

DefaultLoginMethod::DefaultLoginMethod(const std::string &description) :
        m_description(description) {
}

const std::string &DefaultLoginMethod::description() const {
    return m_description;
}

LoginMethodFactory::LoginMethodFactory() :
        m_login_method_names({
            "DEFAULT", "SASL", "SASL_EXTERNAL", "PASSWORD",
            "NICKSERV_MSG", "NICKSERV_CMD", "CHALLENGE", "CUSTOM"
        }) {
    auto it = m_login_method_names.begin();
    m_login_methods[*(it++)] = std::unique_ptr<LoginMethod>(new DefaultLoginMethod("Default"));
    m_login_methods[*(it++)] = std::unique_ptr<LoginMethod>(new DefaultLoginMethod("SASL (username + password)"));
    m_login_methods[*(it++)] = std::unique_ptr<LoginMethod>(new DefaultLoginMethod("SASL EXTERNAL (cert)"));
    m_login_methods[*(it++)] = std::unique_ptr<LoginMethod>(new DefaultLoginMethod("Server password (/PASSWORD password)"));
    m_login_methods[*(it++)] = std::unique_ptr<LoginMethod>(new DefaultLoginMethod("NickServ (/MSG NickServ + password)"));
    m_login_methods[*(it++)] = std::unique_ptr<LoginMethod>(new DefaultLoginMethod("NickServ (/NICKSERV + password)"));
    m_login_methods[*(it++)] = std::unique_ptr<LoginMethod>(new DefaultLoginMethod("Challege Auth (username + password)"));
    m_login_methods[*(it++)] = std::unique_ptr<LoginMethod>(new DefaultLoginMethod("Custom... (connect commands)"));
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

std::vector<std::string> LoginMethodFactory::get_login_methods() {
    return std::vector<std::string>(m_login_method_names);
}

}
