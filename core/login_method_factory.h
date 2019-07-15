#ifndef LOGIN_METHOD_FACTORY_H
#define LOGIN_METHOD_FACTORY_H

#include <unordered_map>
#include <memory>
#include <boost/optional.hpp>
#include "login_method.h"

namespace core {

class LoginMethodFactory {
public:
    LoginMethodFactory();
    const std::string &get_default_method();
    boost::optional<LoginMethod &> find_login_method(const std::string &name);

private:
    std::unordered_map<std::string, std::unique_ptr<LoginMethod>> m_login_methods;
    static const std::string s_default_method;
};

class DefaultLoginMethod : public LoginMethod {
};

}

#endif // LOGIN_METHOD_FACTORY_H
